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
  struct sockaddr_in host_addr, client_addr;
  struct hostent *host;
  socklen_t size;
  int recv_length;
  char buffer[BUF_SIZE];
/*
  host = gethostbyname("dongwon2");
  if(host) {
    fprintf(stderr, "NAME : %s \n", host->h_name);
  } else {
    fprintf(stderr, "NO host corresponding ip\n");
  }
*/
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

  size = sizeof(struct sockaddr_in);
  if((accepted_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &size)) == -1) {
    fprintf(stderr, "accept error\n");
    exit(0);
  }

//  fprintf(stderr, "Client INFO - Host Name : %s\n", );
  fprintf(stderr, "Client INFO - IP Address : %s\n", inet_ntoa(client_addr.sin_addr));
  fprintf(stderr, "Client INFO - PORT : %d\n", ntohs(client_addr.sin_port));

  //strcpy(buffer, inet_ntoa(client_addr.sin_addr));


  //send(accepted_fd, buffer, sizeof(buffer), 0);

  strcpy(buffer, inet_ntoa(client_addr.sin_addr));
  send(accepted_fd, buffer, sizeof(buffer), 0);

  int portnum = ntohs(client_addr.sin_port);
  sprintf(buffer, "%d", portnum);
  send(accepted_fd, buffer, sizeof(buffer), 0);

  close(accepted_fd);

  return 0;
}

