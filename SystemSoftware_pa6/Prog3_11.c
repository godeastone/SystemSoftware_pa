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

static int SemID;

void p()
{
  struct sembuf pbuf;

  pbuf.sem_num = 0;
  pbuf.sem_op = -1;
  pbuf.sem_flg = SEM_UNDO;

  if(semop(SemID, &pbuf, 1) == -1) {
    fprintf(stderr, "p-semop failed\n");
    exit(0);
  }
}

void v()
{
  struct sembuf vbuf;

  vbuf.sem_num = 0;
  vbuf.sem_op = 1;
  vbuf.sem_flg = SEM_UNDO;

  if(semop(SemID, &vbuf, 1) == -1) {
    fprintf(stderr, "v-semop failed\n");
    exit(0);
  }
}

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
};

int main(int argc, char *argv[])
{
  int shmid;
  int key1, key2;
  void *memory_segment = NULL;

  union semun sem_union;

  if((shmid = shmget((key_t)key, sizeof(char), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment = shmat(shmid, (void *)0, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  if((SemID = semget(IPC_PRIVATE, 1, IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "semget failed\n");
    exit(0);
  }

  //set semaphore value as 1
  sem_union.val = 1;

  if(semctl(SemID, 0, SETVAL, sem_union) == -1) {
    fprintf(stderr, "semctl failed\n");
    exit(0);
  }

  for(int i = 0; i < 10; i++) {
    p();
    strcpy((char *)(memory_segment), "System");
    sleep(1);
    fprintf(stderr, "A : %s\n", (char *)memory_segment);
    v();
  }

  if(semctl(SemID, 0, IPC_RMID, sem_union) == -1) {
    fprintf(stderr, "semctl2 failed\n");
    exit(0);
  }

  return 0;
}
