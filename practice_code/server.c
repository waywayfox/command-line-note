#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define LISTEN_PORT "3490"
#define BACKLOG 10


int main(int argc, char *argv[])
{
  char inputBuffer[256] = {0};
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  int sockfd, new_fd;
  int i = 0;
  int result = 0;

  if (argc != 2)
  {
    fprintf(stderr, "usage: server port\n");
    return 1;
  }

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  result = getaddrinfo("localhost", argv[1], &hints, &res);
  if (result != 0)
  {
    return 1;
  }

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd == -1)
  {
    perror("socket create");
    return 1;
  }

  char yes='1';
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    return 1;
  }

  printf("server sockfd %d\n", sockfd);
  result = bind(sockfd, res->ai_addr, res->ai_addrlen);
  if (result == -1)
  {
    perror("bind");
    return 1;
  }

  result = listen(sockfd, BACKLOG);
  if (result == -1)
  {
    perror("listen");
    return 1;
  }


  addr_size = sizeof their_addr;

  while (1)
  {
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_fd == -1)
    {
      perror("accept");
      continue;
    }

    memset(inputBuffer, 0, sizeof(inputBuffer));
    recv(new_fd, inputBuffer, sizeof(inputBuffer), 0);
    if (strlen(inputBuffer) != 0)
    {
      for (i = 0; i < strlen(inputBuffer); i++)
      {
        inputBuffer[i] = toupper((int)inputBuffer[i]);
      }
      result = send(new_fd, inputBuffer, sizeof(inputBuffer), 0);
    }

  }
  freeaddrinfo(res);
  shutdown(sockfd, 2);
  return 0;

}











