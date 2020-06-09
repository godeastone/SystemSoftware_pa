#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define key 5678
#define key_sem 123

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
};

int SemID;

int main(int argc, char *argv[])
{
  int shmid;
  int key1, key2;
  void *memory_segment = NULL;

  union semun sem_union;
  struct sembuf sem_open = {0, -1, SEM_UNDO};
  struct sembuf sem_close = {0, 1, SEM_UNDO};

  if((shmid = shmget((key_t)key, sizeof(char), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment = shmat(shmid, (void *)0, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  if((SemID = semget((key_t)key_sem, 1, IPC_CREAT|IPC_EXCL|0666)) -1) {
    if((SemID = semget((key_t)key_sem, 0, 0)) == -1) {
        fprintf(stderr, "semget failed\n");
        exit(0);
    }
  } else {
    fprintf(stderr, "Create new semaphore segment\n.");
  }

  sem_union.val = 1;
  semctl(SemID, 0, SETVAL, sem_union);

  if(semop(SemID, &sem_open, 1) == -1) {
    fprintf(stderr, "semop failed\n");
    exit(0);
  }

  for(int i = 0; i < 10; i++) {
    strcpy((char *)(memory_segment), "System");
    sleep(1);
    fprintf(stderr, "A : %s\n", memory_segment);
  }

  semop(SemID, &sem_close, 1);

  return 0;
}
