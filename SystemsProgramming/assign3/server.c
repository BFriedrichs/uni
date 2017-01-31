#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "messaging.h"
#include "shared.h"

#define CLIENT_SIZE 5

#define true 1
#define false 0
#define bool int

void handle_connected_client(int clientfd);
bool evaluate_input(int *result);
char *show_scoreboard();
int check_winner(int result);

int signals[] = {
  SIGINT,
  SIGTERM,
  SIGHUP
};
int signals_len = sizeof(signals)/sizeof(int);

char *CLIENT_NAME;
pid_t PID = 0;
int socketfd = 0;

shared_mem_t *SHARED_MEM;
char *MESSAGE_BUFFER;
int VALUE_TO_REACH = 0;
int VALUES_TO_USE[7] = {0, 0, 0, 0, 0, 0, 0};

void sig_handler(int signo) {
  if(PID == 0) {  // if parent
    close_shared_memory(SHARED_MEM);
    destroy_semaphore();
  } else {
    printf("Client disconnected! Shutdown this socket. (%s)\n", CLIENT_NAME);
  }

  free(SHARED_MEM);
  shutdown(socketfd, SHUT_RDWR);
  close(socketfd);

  exit(1);
}

int main(int argc, char *argv[]) {
  bool isDone = false;

  struct sockaddr_in server, client;
  int portno = 0;

  bool eflag = false, nflag = false, pflag = false;
  int arg;

  while (optind < argc) {
    arg = getopt(argc, argv, "e:n:p:");
    if(arg == -1) {
      optind++;
      continue;
    }

    switch (arg) {
      case 'e':
        eflag = true;
        int offset = 0, old_offset = 0;
        for(int i = 0; i < 7; i++) {
          while(optarg[offset]) {
            offset++;
          }
          int diff = offset - old_offset;
          char numstr[diff + 1];
          numstr[diff] = '\0';

          memcpy(numstr, &optarg[old_offset], diff);

          int num = atoi(numstr);
          if(num <= 1 || num >= 100) {
            perror("All -e arguments have to be between 1 and 100");
            exit(1);
          }

          VALUES_TO_USE[i] = num;
          offset++;
          old_offset = offset;
        }
        break;
      case 'n':
        nflag = true;
        int num = atoi(optarg);
        if(num <= 1 || num >= 1000) {
          perror("The -n arguments has to be between 1 and 1000");
          exit(1);
        }

        VALUE_TO_REACH = num;
        break;
      case 'p':
        pflag = true;
        portno = atoi(optarg);
        break;
    }
  }

  if(!eflag || !nflag || !pflag || VALUES_TO_USE[6] == 0) { // hacky but ok for now
    perror("You have to start the server using -e, -n and -p");
    exit(1);
  }

  printf("Server initialised: \n");
  printf("\t Port: %i\n", portno);
  printf("\t Numbers: ");

  for(int i = 0; i < 7; i++) { printf("%i ", VALUES_TO_USE[i]); }
  printf("\n\t Number to reach: %i\n", VALUE_TO_REACH);

  socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(socketfd < 0) {
    perror("can't socket");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_port = portno;
  server.sin_addr.s_addr = INADDR_ANY;

  if(bind(socketfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("can't bind");
    exit(1);
  }

  if(listen(socketfd, CLIENT_SIZE) < 0) {
    perror("can't listen");
    exit(1);
  }

  int client_len = sizeof(client);

  // catch signals
  for(int i = 0; i < signals_len; i++) {
    signal(signals[i], sig_handler);
  }

  SHARED_MEM = get_shared_memory();
  create_sempaphore();

  while(!isDone) {
    int clientfd = accept(socketfd, (struct sockaddr *) &client, &client_len);

    if(clientfd < 0) {
      perror("couldn't accept client");
    } else {
      printf("Client connected!\n");
      int child_pid = fork();
      if(child_pid == 0) {  // child gets 0, parent gets childs pid
        // in child
        PID = getpid();

        handle_connected_client(clientfd);
      } else {
        // in parent

      }
    }
  }
}

void handle_connected_client(int clientfd) {

  // Get initial client name for later use
  MESSAGE_BUFFER = read_message(clientfd);
  CLIENT_NAME = malloc(strlen(MESSAGE_BUFFER));
  strcpy(CLIENT_NAME, MESSAGE_BUFFER);
  free(MESSAGE_BUFFER);

  // send welcome string
  char welcome_str[50];
  sprintf(welcome_str, "Hello %s, welcome to the server!\n", CLIENT_NAME);

  send_message(clientfd, welcome_str);

  while(1) {
    char menu[256];
    sprintf(menu, "The number to reach is: %i\n"
                  "You can use: %i %i %i %i %i %i %i\n"
                  "You can do one of the following actions:\n"
                  "\t1) Type a term in postfix notation (a result must be greater than 0 and smaller than %i)\n"
                  "\t2) Type \"TOP\" to see the leaderboard\n"
                  "\t3) Type \"QUIT\" to exit\n",
                  VALUE_TO_REACH,
                  VALUES_TO_USE[0],
                  VALUES_TO_USE[1],
                  VALUES_TO_USE[2],
                  VALUES_TO_USE[3],
                  VALUES_TO_USE[4],
                  VALUES_TO_USE[5],
                  VALUES_TO_USE[6],
                  VALUE_TO_REACH * 2);

    send_message(clientfd, menu);

    MESSAGE_BUFFER = read_message(clientfd);

    printf("%s\n", MESSAGE_BUFFER);
    if(strcmp(MESSAGE_BUFFER, "TOP") == 0) {
      lock_semaphore();
      char *sb = show_scoreboard();
      unlock_semaphore();
      send_message(clientfd, sb);
      free(sb);
    } else if(strcmp(MESSAGE_BUFFER, "QUIT") == 0) {
      send_message(clientfd, "Ok, Bye");
      sig_handler(0);
    } else {
      int result = 0;
      if(evaluate_input(&result)) {
        char msg[256];
        lock_semaphore();
        int lb_index = check_winner(result);
        unlock_semaphore();
        if(lb_index >= 0) {
          sprintf(msg, "Congratulations!\n"
                        "Your score %i has been added to the #%i position on the leaderboard!",
                        result,
                        lb_index + 1);
        } else {
          sprintf(msg, "Your score %i was sadly not good enough to be added to the leaderboard, try again!",
                        result);
        }
        send_message(clientfd, msg);
      } else {
        send_message(clientfd, "Wrong input!");
      }
    }

    free(MESSAGE_BUFFER);
  }
}

/**
 * ! NEEDS SEMAPHORE !
 *
 * Create Scoreboard
 */
char *show_scoreboard() {
  char *result = malloc(500);
  sprintf(result, "%s", "The Scoreboard:\n"
                        "\tNAME\t|\tSCORE\t\n"
                        "\t\t|\t\t\n");

  for(int i = 0; i < 10; i++) {
    sprintf(result + strlen(result), "\t%s\t|", &SHARED_MEM->names[i * 20]);
    sprintf(result + strlen(result), "\t%i\t\n", SHARED_MEM->scores[i]);
  }

  return result;
}

/**
 * ! NEEDS SEMAPHORE !
 *
 * Checks if the result belongs in the leaderboard
 * if it does adjust leaderboard and return leaderboard index
 */
int check_winner(int result) {
  int diff_res = abs(result - VALUE_TO_REACH);
  for(int i = 0; i < 10; i++) {
    int diff_lb = abs(SHARED_MEM->scores[i] - VALUE_TO_REACH);

    if(diff_res < diff_lb) {
      for(int j = 9; j > i; j--) {
        SHARED_MEM->scores[j] = SHARED_MEM->scores[j - 1];
        snprintf(&SHARED_MEM->names[j * 20], 20, "%s", &SHARED_MEM->names[(j - 1) * 20]);
      }
      SHARED_MEM->scores[i] = result;
      snprintf(&SHARED_MEM->names[i * 20], 20, "%s", CLIENT_NAME);
      return i;
    }
  }
  return -1;
}

bool calc(int *result, int left, int right, char op) {
  switch(op) {
    case '+':
      *result = left + right;
      break;
    case '-':
      *result = left - right;
      break;
    case '*':
      *result = left * right;
      break;
    case '/':
      *result = left / right;
      break;
    default:
      return false;
  }

  return true;
}

bool in_values(int val) {
  for(int i = 0; i < 7; i++) {
    if(val == VALUES_TO_USE[i]) {
      return true;
    }
  }
  return false;
}

bool evaluate_input(int *result) {
  char *token = strtok(MESSAGE_BUFFER, " ");
  int results[256];
  int count = 0;

  int left = 0, right = 0;
  bool left_flag = false, right_flag = false;

  while(token != NULL) {
    bool is_digit = true;
    for(int i = 0; i < strlen(token); i++) {
      if(!isdigit(*(token + i))) {
        is_digit = false;
        break;
      }
    }
    if(is_digit) {
      int val = atoi(token);
      if(!in_values(val)) {
        return false;
      }
      if(!left_flag) {
        left = val;
        left_flag = true;
      } else if(!right_flag) {
        right = val;
        right_flag = true;
      } else {
        results[count++] = left;
        left = right;
        right = val;
      }
    } else {
      if(strlen(token) == 1) {
        if(left_flag && right_flag) {
          if(!calc(&left, left, right, *token)) {
            return false;
          }
          right = 0;
          right_flag = false;
        } else if(left_flag && !right_flag){
          if(count > 0) {
            if(!calc(&left, left, results[--count], *token)) {
              return false;
            }
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        return false;
      }
    }

    token = strtok(NULL, " ");
  }
  if(count > 0) {
    return false;
  }
  
  *result = left;
  return true;
}
