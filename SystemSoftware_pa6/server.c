#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_NAME "dongwonsocket"
#define BUF_SIZE 256
int main()
{
  char buf[BUF_SIZE];
  struct sockaddr_in ser, cli;
  int socket_fd, nsd, len, clen;

  if((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  memset((char *)&ser, 0, sizeof(struct sockaddr_un));
  ser.sun_family = AF_UNIX;
  strcpy(ser.sun_path, SOCKET_NAME);
  len = sizeof(ser.sun_family) + strlen(ser.sun_path);

  if(bind(sd, (struct sockaddr *)&ser, len)) {
    perror("bind error");
    exit(1);
  }

  if(listen(sd, 5) < 0) {
    perror("listen error");
    exit(1);
  }

  fprintf(stderr, "Waiting ... \n");

  if((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) {
    perror("accept error");
    exit(1);
  }

  if(recv(nsd, buf, sizeof(buf), 0) == -1) {
    perror("recv error");
    exit(1);
  }

  fprintf(stderr, "Received Message : %s\n", buf);
  close(nsd);
  close(sd);

  return 0;
}
