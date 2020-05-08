#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  sigset_t sig;
  sigemptyset(&sig);
  sigaddset(&sig, SIGINT);
  sigprocmask(SIG_BLOCK, &sig, NULL);

  while(1) {
    printf("System software\n");
    sleep(1);
  }

  return 0;
}
