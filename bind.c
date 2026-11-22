#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main() {
    int sockfd;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // IP of the host
    getaddrinfo(NULL, "3090", &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    return 0;
}