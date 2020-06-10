#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define key 1234

int main(int argc, char *argv[])
{
  int shmid;
  void *memory_segment = NULL;

  if((shmid = shmget((key_t)key, sizeof(char), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment = shmat(shmid, (void *)0, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  for(int i = 0; i < 10; i++) {
    strcpy((char *)memory_segment, "System");
    fprintf(stderr, "A : %s\n", (char *)memory_segment);
    sleep(1);
  }

  if(shmdt(memory_segment) == -1) {
      fprintf(stderr, "shmdt failed\n");
  }

  return 0;
}
