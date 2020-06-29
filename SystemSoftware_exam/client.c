#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 5678
#define BUF_SIZE 100

int main(int args, char *argv[])
{
  int sd, len;
  char buffer[BUF_SIZE];
  struct sockaddr_in ser;

  if((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(1);
  }

  memset((char *)&ser, 0, sizeof(ser));
  ser.sin_family = AF_INET;
  ser.sin_addr.s_addr = inet_addr("192.168.0.112");
  ser.sin_port = htons(PORT);

  if(connect(sd, (struct sockaddr *)&ser, sizeof(ser)) < 0) {
    perror("bind error");
    exit(1);
  }

  strcpy(buffer, "goto hell\n");

  send(sd, buffer, sizeof(buffer), 0);

  close(sd);

  return 0;
}
