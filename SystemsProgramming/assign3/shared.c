
#include "shared.h"

#define SEM_KEY 12345
#define SM_KEY_SCORES 5678
#define SM_KEY_NAMES 6789
/*
 flag 0666 is equivalent to "S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH"
 -> read-write for all
*/

int shmid_scores, shmid_names;
int semid;

shared_mem_t *get_shared_memory() {

  int *sh_mem_scores;
  char *sh_mem_names;

  if((shmid_scores = shmget(SM_KEY_SCORES, sizeof(int) * 10, IPC_CREAT | 0666)) < 0) {
    perror("can't shmget");
    exit(1);
  }

  if ((sh_mem_scores = shmat(shmid_scores, NULL, 0)) < 0) {
    perror("can't shmat");
    exit(1);
  }

  if((shmid_names = shmget(SM_KEY_NAMES, sizeof(char) * 20 * 10, IPC_CREAT | 0666)) < 0) {
    perror("can't shmget");
    exit(1);
  }

  if ((sh_mem_names = shmat(shmid_names, NULL, 0)) < 0) {
    perror("can't shmat");
    exit(1);
  }

  shared_mem_t *shared_mem;
  shared_mem = malloc(sizeof(shared_mem_t));

  shared_mem->scores = sh_mem_scores;
  shared_mem->names = sh_mem_names;

  return shared_mem;
}

void close_shared_memory(shared_mem_t *shared_mem) {
  if(shmdt(shared_mem->scores) < 0) {
    perror("can't shmdt");
    exit(1);
  }
  if(shmdt(shared_mem->names) < 0) {
    perror("can't shmdt");
    exit(1);
  }

  shmctl(shmid_scores, IPC_RMID, NULL);
  shmctl(shmid_names, IPC_RMID, NULL);
}

void create_sempaphore() {
  int semflg = IPC_CREAT | 0666;

  if((semid = semget(SEM_KEY, 1, semflg)) == -1) {
    perror("can't semaphore");
    exit(1);
  }
}

void lock_semaphore() {
  struct sembuf sem_lock[] = {{ 0, 0, SEM_UNDO }, { 0, 1, SEM_UNDO | IPC_NOWAIT }};

  if (semop(semid, sem_lock, 2) == -1) {
		perror("can't semop wait");
    exit(1);
	}
}

void unlock_semaphore() {
  struct sembuf sem_unlock = { 0, -1, IPC_NOWAIT };

  if (semop(semid, &sem_unlock, 1) == -1) {
		perror("can't semop release");
    exit(1);
	}
}

void destroy_semaphore() {
  semctl(semid, 0, IPC_RMID);
}
