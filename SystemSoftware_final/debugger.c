#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
  pid_t child_pid;

  fflush(stdin);
  child_pid = fork();

  //fprintf(stderr, "->%s<-\n", *(argv+1));

  if(child_pid == 0) {
    //Child
    execl("/usr/bin/gcc", "/usr/bin/gcc", *(argv+1), NULL);

      //error control
    fprintf(stderr, "!ERROR! - fork failed.\n");
  }

  return 0;
}
