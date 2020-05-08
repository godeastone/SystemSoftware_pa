#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int sig_num)
{
  printf("Received Signal :: Quit\n");
  sleep(2);
  printf("After Signal Handler\nprogram end\n");
  kill(getpid(), SIGINT);
}

int main()
{
  struct sigaction sig;
  /*set signal handler*/
  sig.sa_handler = signal_handler;
  sigemptyset(&sig.sa_mask);
  sig.sa_flags = 0;
  sigaction(SIGQUIT, &sig, NULL);

  fprintf(stderr, "Input SIGQUIT:");
  for(;;) {
  }

  return 0;
}
