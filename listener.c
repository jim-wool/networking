#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MYPORT "4956"
#define MAXLEN 100

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main() {
    int sockfd;
    struct addrinfo hints, *res, *p;
    struct sockaddr_storage their_addr;
    int rv;
    int numbytes;
    char s[INET6_ADDRSTRLEN];
    char buf[MAXLEN];
    socklen_t addr_len;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &res)) == -1) {
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(rv));
        return 1;
    }
    for (p = res; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("listener: bind");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }
    freeaddrinfo(res);
    printf("listener: waiting to recvfrom\n");
    addr_len = sizeof(their_addr);
    if ((numbytes = recvfrom(sockfd, buf, MAXLEN-1, 0,(struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        return 1;
    }
    printf("listener: got packet from %s\n", inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr*)&their_addr), s, INET6_ADDRSTRLEN));
    printf("listener: paquet is %d bytes long.\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: paquet contains: %s\n", buf);
    close(sockfd);
    return 1;
}