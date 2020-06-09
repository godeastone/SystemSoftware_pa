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
  int key1, key2;
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
    strcpy((char *)(memory_segment), "Prog");
    sleep(1);
    fprintf(stderr, "B : %s\n", memory_segment);
  }

  return 0;
}
