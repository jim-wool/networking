#include <stdio.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in sa;
    inet_pton(AF_INET, "192.168.0.1", &(sa.sin_addr));
    char buff[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sa.sin_addr), buff, INET_ADDRSTRLEN);
    printf("%s\n", buff);
    return 0;
}