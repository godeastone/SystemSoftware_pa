#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define SOCKET_NAME "dongwonsocket"
#define BUF_SIZE 256

int main()
{
  int sd, len;
  char buf[BUF_SIZE];
  struct sockadder_un ser;

  if((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(1);
  }

  memset((char *)&ser, '\0', sizeof(ser));
  ser.sun_family = AF_UNIX;
  strcpy(ser.sun_path, SOCKET_NAME);
  len = sizeof(ser.sun_family) + strlen(ser.sun_path);

  if(connect(sd, (struct sockaddr *)&ser, len) < 0) {
    perror("bind error");
    exit(1);
  }

  strcpy(buf, "Unix Domain Socket Test Message\n");

  if(send(sd, buf, sizeof(buf), 0) == -1) {
    perror("sned error");
    exit(1);
  }

  close(sd);

  return 0;
}
