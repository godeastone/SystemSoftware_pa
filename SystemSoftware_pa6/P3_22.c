#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define key 5678
#define key_sema 1234

static int SemID;

void sem_lock(int sem_set_id)
{
  struct sembuf sem_op;

  sem_op.sem_num = 0;
  sem_op.sem_op = -1;
  sem_op.sem_flg = 0;

  if(semop(sem_set_id, &sem_op, 1) == -1) {
    fprintf(stderr, "p-semop failed\n");
    exit(0);
  }
}

void sem_unlock(int sem_set_id)
{
  struct sembuf sem_op;

  sem_op.sem_num = 0;
  sem_op.sem_op = 1;
  sem_op.sem_flg = 0;

  if(semop(sem_set_id, &sem_op, 1) == -1) {
    //fprintf(stderr, "v-semop failed\n");
    //exit(0);
  }
}


int main(int argc, char *argv[])
{
  union semun
  {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
  }sem_val;

  int shmid;
  int key1, key2;
  void *memory_segment = NULL;
  struct shmid_ds shm_desc;

  if((SemID = semget((key_t)key_sema, 1, IPC_CREAT|0666)) == -1) {
    fprintf(stderr, "semget failed\n");
    exit(0);
  }

  sem_val.val = 1;

  if(semctl(SemID, 0, SETVAL, sem_val) == -1) {
    fprintf(stderr, "semctl failed\n");
    exit(0);
  }

  if((shmid = shmget((key_t)key, sizeof(char), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment = shmat(shmid, (void *)0, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  for(int i = 0; i < 10; i++) {
    sem_lock(SemID);
    strcpy((char *)(memory_segment), "Prog");
    fprintf(stderr, "B : %s\n", (char *)memory_segment);
    sleep(1);
    sem_unlock(SemID);
  }

  if(shmdt(memory_segment) == -1) {
    fprintf(stderr, "shmdt error\n");
    exit(0);
  }

  if(shmctl(shmid, IPC_RMID, &shm_desc) == -1) {
    fprintf(stderr, "shmctl erorr\n");
    exit(0);
  }

  if(semctl(SemID, 0, IPC_RMID, sem_val) == -1) {
    fprintf(stderr, "semctl2 failed\n");
    exit(0);
  }

  return 0;
}
