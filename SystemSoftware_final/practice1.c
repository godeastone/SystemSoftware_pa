#include <stdio.h>
#include <string.h>

void f(void) {
  char buf[100];
  memcpy(buf, "hello, world", 1024);
}

int main(int argc, char *argv[])
{
  int a = 10;
  int *p = NULL;
  int arr[5];

  //arr[5000] = 11;
  //*p = 10;

  //f();

  fprintf(stderr, "HELLO\n");


  return 0;
}


