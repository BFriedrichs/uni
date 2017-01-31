#include "messaging.h"

void send_message(int fd, char message[]) {
  int size = strlen(message);

  if(send(fd, (char *) &size, sizeof(size), 0) < 0) {
    perror("can't write");
    exit(1);
  }

  if(send(fd, message, size, 0) < 0) {
    perror("can't write");
    exit(1);
  }
}

char* read_message(int fd) {
  int len = 0;
  if(recv(fd, (char *) &len, sizeof(len), 0) < 0) {
    perror("can't read");
    exit(1);
  }

  char *buffer = malloc(len + 1);

  if(recv(fd, buffer, len, 0) < 0) {
    perror("can't read");
    exit(1);
  }
  buffer[len] = '\0';

  return buffer;
}

void read_and_print_message(int fd) {
  char *message = read_message(fd);
  printf("%s\n", message);
  free(message);
}
