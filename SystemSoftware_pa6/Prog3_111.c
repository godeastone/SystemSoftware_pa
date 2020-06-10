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

int SemID;

int main(int argc, char *argv[])
{
  int shmid;
  int key1, key2;
  void *memory_segment = NULL;
  int semId, proId, smId;

  struct sembuf semB;


  if((shmid = shmget((key_t)key, sizeof(char), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment = shmat(shmid, (void *)0, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  semB.sem_flg = SEM_UNDO;
  semB.sem_num = 0;

  if(semId = semget((key_t)123, 1, 0666 | IPC_CREAT) == -1) {
    fprintf(stderr, "semget failed\n");
  }

  if(semctl(semId, 0, SETVAL, 1) == -1) {
    fprintf(stderr, "semctl failed\n");
    exit(0);
  }


  for(int i = 0; i < 10; i++) {
    semB.sem_op = -1;
    if(semop(semId, &semB, 1) == -1) {
      fprintf(stderr, "semop 48 failed\n");
      exit(0);
    }

    strcpy((char *)(memory_segment), "System");
    sleep(1);
    fprintf(stderr, "A : %s\n", (char *)memory_segment);

    semB.sem_op = 1;
    if(semop(semId, &semB, 1) == -1) {
      fprintf(stderr, "semop57 failed\n");
      exit(0);
    }
  }

  if(semctl(semId, 0, IPC_RMID, 0) == -1) {
    fprintf(stderr, "semctl2 failed\n");
    exit(0);
  }

  return 0;
}
