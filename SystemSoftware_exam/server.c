#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define BUF_SIZE 100
#define PORT 5678

int main(int argc, char *argv[])
{
  struct sockaddr_in server_adr, client_adr;
  int address_size;
  int server_sock, client_sock;
  char buffer[BUF_SIZE];

  server_sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&server_adr, 0, sizeof(server_adr));
  server_adr.sin_family = AF_INET;
  server_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_adr.sin_port = htons(PORT);

  if(bind(server_sock, (struct sockaddr *)&server_adr, sizeof(server_adr)) == -1) {
    perror("bind error!\n");
    return EXIT_FAILURE;
  }

  if(listen(server_sock, 5) == -1) {
    perror("listen error!\n");
    return EXIT_FAILURE;
  }

  address_size = sizeof(struct sockaddr_in);

  if((client_sock = accept(server_sock, (struct sockaddr *)&client_adr, &address_size)) == -1) {
    perror("accept error!\n");
    return EXIT_FAILURE;
  }

  strcpy(buffer, "hello\n");
  send(client_sock, buffer, sizeof(buffer), 0);

  close(server_sock);

  return 0;
}


