#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVERPORT "4956"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: hostname message");
        return 1;
    }
    int sockfd, rv, numbytes;
    struct addrinfo hints, *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(rv));
        return 1;
    }
    for (p = res; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }
    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0, p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        return 1;
    }
    printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    freeaddrinfo(res);
    close(sockfd);
    return 0;
}