#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MAX_DATA_SIZE 1024

#define IAC 0xFF
#define WILL 0xFB
#define WONT 0xFC
#define DO 0xFD
#define DONT 0xFE

void print_hex(char* str) {
  fprintf(stdout, "ServerHEX: ");
  while (*str) {
    if (*str != '\0')
      fprintf(stdout, "%x ", *str);
    str++;
  }
  puts("");
}

void remove_endline(char* str) {
  while (*str) {
    if (*str == '\n') {
      *str = '\0';
    }
    str++;
  }
}

int main(int argc, char** argv) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s HOST [PORT]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int rc, sockfd;
  char port[5];
  if (argv[2] == NULL) {
    strcpy(port, "23");
  } else {
    remove_endline(argv[2]);
    strcpy(port, argv[2]);
  }

  struct addrinfo hint, *res;
  memset(&hint, 0, sizeof(struct addrinfo));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  fprintf(stdout, "trying: %s:%s\n", argv[1], port);
  rc = getaddrinfo(argv[1], port, &hint, &res);
  if (rc != 0) {
    fprintf(stdout, "getaddrinfo(): %d\n%s\n", rc, gai_strerror(rc));
  }

  // iterate over res and make the socket
  struct addrinfo *p = res;
  for (; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd < 0) {
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) {
      break;
    }

    close(sockfd);
  }
  freeaddrinfo(res);

  char ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, (struct sockaddr_in*)p, ip, sizeof ip);
  fprintf(stdout, "ip: %s\n", ip);
  if (p == NULL) {
    perror("getaddrinfo() failed");
    exit(EXIT_FAILURE);
  }
 
  // make the socket non blocking
  /*rc = fcntl(sockfd, F_SETFL, O_NONBLOCK);
  if (rc < 0) {
    perror("fcntl() failed");
    exit(EXIT_FAILURE);
  }*/

  // connect to the server
  fprintf(stdout, "Connected to... %s:%s\n", argv[1], port);

  char buf[MAX_DATA_SIZE];
  while (1) {
    rc = recv(sockfd, buf, sizeof buf, 0);
    if (rc == 0) {
      fprintf(stdout, "Connection closed\n");
      break;
    }
    buf[rc] = '\0';
    fprintf(stdout, "ServerSTR: %s\n", buf);
    print_hex(buf);
  }

  // close the socket
  close(sockfd);

  exit(EXIT_SUCCESS);
}

