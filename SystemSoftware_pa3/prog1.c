#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, const char *argv[])
{
  pid_t pid;

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
    printf("Parent Process : End\n");
    exit(0);
  }

  return 0;
}
