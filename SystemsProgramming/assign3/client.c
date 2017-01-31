#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "messaging.h"

int signals[] = {
  SIGINT,
  SIGTERM,
  SIGHUP
};
int signals_len = sizeof(signals)/sizeof(int);

int SOCKETFD = 0;
char *HOST_NAME;

char *get_user_input();

void sig_handler(int signo) {
  printf("signal handled\n");

  send_message(SOCKETFD, "QUIT");

  shutdown(SOCKETFD, SHUT_RDWR);
  close(SOCKETFD);

  exit(1);
}

int main(int argc, char* argv[]) {
  struct sockaddr_in connection;
  int isDone = 0;

  int hflag = 0, pflag = 0;
  int portno = 0;


  int arg;
  while ((arg = getopt(argc, argv, "h:p:")) != -1) {
    switch (arg) {
      case 'h':
        hflag = 1;
        if(strlen(optarg) > 20) {
          perror("Hostname length is max. 20!");
          exit(1);
        }
        HOST_NAME = malloc(strlen(optarg));
        strcpy(HOST_NAME, optarg);
        break;
      case 'p':
        pflag = 1;
        portno = atoi(optarg);
        break;
      default:
        printf("%s\n", optarg);
        break;
    }
  }

  if(!hflag || !pflag) {
    perror("You have to start the client using -h and -p");
    exit(1);
  }

  SOCKETFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(SOCKETFD < 0) {
    perror("can't socket");
    exit(1);
  }

  connection.sin_family = AF_INET;
  connection.sin_port = portno;
  connection.sin_addr.s_addr = INADDR_ANY;

  if(connect(SOCKETFD, (struct sockaddr *) &connection, sizeof(connection)) < 0) {
    perror("can't connect");
    exit(1);
  }

  for(int i = 0; i < signals_len; i++) {
    signal(signals[i], sig_handler);
  }

  send_message(SOCKETFD, HOST_NAME); // initially send host name
  read_and_print_message(SOCKETFD); // connection message

  while(1) {
    read_and_print_message(SOCKETFD); // menu

    printf("Your command: ");
    char *input = get_user_input();

    send_message(SOCKETFD, input);

    printf("\n\n");
    read_and_print_message(SOCKETFD); // get response
    for(int i = 0; i < 50; i++) {
      printf("=");
    }
    printf("\n\n");

    if(strcmp(input, "QUIT") == 0) {
      sig_handler(0);
    }

    free(input);
  }

  return 0;
}

char *get_user_input() {
  int bufsize = 256;
  char input[bufsize];
  memset(input, 0, bufsize);

  fgets(input, bufsize, stdin);

  int len = strlen(input);
  input[len - 1] = '\0'; // \0 instead of \n

  char *result = malloc(len);
  memset(result, 0, len);

  strcpy(result, input);

  return result;
}
