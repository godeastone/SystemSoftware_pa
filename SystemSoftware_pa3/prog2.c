#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, const char *argv[])
{
  int pid;
  int status;

  pid = fork();
  if(pid == 0) {
    //Child
    printf("Child Process : Begin\n");
    system("who");
    printf("Child Process : End\n");
    exit(0);
  } else {
    //Parent
    printf("Parent Process : Begin\n");
    system("date");
    wait(&status);
    printf("$%d\n", status);
    printf("Parent Process : End\n");
    exit(0);
  }

  return 0;
}
