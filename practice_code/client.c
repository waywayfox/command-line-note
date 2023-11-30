#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>


#define LISTEN_PORT "3490"

int main(int argc, char *argv[])
{
  char message[256] = {0};
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  int sockfd, new_fd;
  int result = 0;

  if (argc != 3)
  {
    fprintf(stderr, "usage: client.o port data\n");
    return 1;
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo("localhost", argv[1], &hints, &res);
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  result = connect(sockfd, res->ai_addr, res->ai_addrlen);
  printf("result connect: %d\n", result);
  if(result != -1)
  {
    send(sockfd, argv[2], strlen(argv[2]), 0);
    recv(sockfd, message, sizeof(message), 0);
    printf("client recv: %s\n", message);

  }
  else
  {
    //printf("connect failed: %d", errno);
    perror("asuka");
  }

  shutdown(sockfd, 2);
  return 0;
}
