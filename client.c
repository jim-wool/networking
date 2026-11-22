#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT "3490"
#define MAXSIZE 100

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: client hostname\n");
        exit(1);
    }
    int sockfd, numbytes;
    char buf[MAXSIZE];
    struct addrinfo hints, *res, *p;
    int rv;
    char s[INET_ADDRSTRLEN];
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], PORT, &hints, &res)) == -1) {
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(rv));
        exit(1);
    }
    for (p = res; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, INET6_ADDRSTRLEN);
        printf("client: attempting to connect to %s\n", s);
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("conenct");
            close(sockfd);
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "client: Failed to connect\n");
        return 2;
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connected to %s\n", s);
    freeaddrinfo(res);
    if ((numbytes = recv(sockfd, buf, MAXSIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    buf[numbytes]='\0';
    printf("client: received '%s'", buf);
    close(sockfd);
    return 0;
}