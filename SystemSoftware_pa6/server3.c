#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
  int socket_fd, accepted_fd;
  struct sockaddr_in host_addr, client_addr;
  socklen_t size;
  int recv_length;
  char buffer[BUF_SIZE];

  if((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "socket error!\n");
    exit(0);
  }

  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(PORT);
  host_addr.sin_addr.s_addr = htons(INADDR_ANY);
  memset(&(host_addr.sin_zero), 0, 8);

  if(bind(socket_fd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1) {
    fprintf(stderr, "bind error!\n");
    exit(0);
  }

  if(listen(socket_fd, 3) == -1) {
    fprintf(stderr, "listen error!\n");
    exit(0);
  }

  while(1) {
    size = sizeof(struct sockaddr_in);
    accepted_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &size);

    send(accepted_fd, "Connected\n", 10, 0);

    fprintf(stderr, "Client Info : Ip : %s, Port : %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    recv_length = recv(accepted_fd, &buffer, BUF_SIZE, 0);

    while(recv_length > 0) {
      fprintf(stderr, "From Client : %s \n", buffer);
      recv_length = recv(accepted_fd, &buffer, BUF_SIZE, 0);
    }
    close(accepted_fd);
  }
  return 0;
}

