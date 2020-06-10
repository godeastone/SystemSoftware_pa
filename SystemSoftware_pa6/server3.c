#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 12345
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
  int socket_fd, accepted_fd;
  struct sockaddr_in host_addr, client_addr, addr;
  struct hostent *host;
  socklen_t size, len;
  int recv_length;
  char buffer[BUF_SIZE], hbuf[30];

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

  size = sizeof(struct sockaddr_in);
  if((accepted_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &size)) == -1) {
    fprintf(stderr, "accept error\n");
    exit(0);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_addr.s_addr = inet_addr("112.214.171.22");
  host = gethostbyaddr((char *)&(client_addr.sin_addr.s_addr), 4, AF_INET);

  fprintf(stderr, "Client INFO - Host Name : %s\n", host->h_name);
  fprintf(stderr, "Client INFO - IP Address : %s\n", inet_ntoa(client_addr.sin_addr));
  fprintf(stderr, "Client INFO - PORT : %d\n", ntohs(client_addr.sin_port));

  //strcpy(buffer, inet_ntoa(client_addr.sin_addr));


  strcpy(buffer, "dongwon2");
  send(accepted_fd, buffer, sizeof(buffer), 0);

  strcpy(buffer, inet_ntoa(client_addr.sin_addr));
  send(accepted_fd, buffer, sizeof(buffer), 0);

  int portnum = ntohs(client_addr.sin_port);
  sprintf(buffer, "%d", portnum);
  send(accepted_fd, buffer, sizeof(buffer), 0);

  close(accepted_fd);

  return 0;
}

