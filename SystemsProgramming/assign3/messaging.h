#ifndef MSG_H
#define MSG_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

void send_message(int fd, char message[]);
char* read_message(int fd);
void read_and_print_message(int fd);

#endif
