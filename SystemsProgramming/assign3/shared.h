#ifndef SHRD_H
#define SHRD_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

typedef struct {
  int *scores;
  char *names;
} shared_mem_t;

shared_mem_t *get_shared_memory();
void close_shared_memory(shared_mem_t *shared_mem);
void create_sempaphore();
void lock_semaphore();
void unlock_semaphore();
void destroy_semaphore();

#endif
