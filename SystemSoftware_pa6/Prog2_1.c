#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char *argv[])
{
  int shmid;
  key_t key1, key2;
  void *memory_segment1 = NULL;
  void *memory_segment2 = NULL;
  char *str1 = "System";
  char *str2 = "Prog";

  key1 = 1234;
  key2 = 5678;

  if((shmid = shmget(key1, sizeof(str1), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((shmid = shmget(key2, sizeof(str2), IPC_CREAT | 0666)) == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(0);
  }

  if((memory_segment1 = shmat(shmid, NULL, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  if((memory_segment2 = shmat(shmid, NULL, 0)) == (void *)-1) {
      fprintf(stderr, "shmat failed\n");
      exit(0);
  }

  str1 = (char *)memory_segment1;
  str2 = memory_segment2;

  fprintf(stderr, "A : %s\n", str1);
  fprintf(stderr, "A : %s\n", str2);

  return 0;
}
