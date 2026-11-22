#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    int s;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.example.com", "3490", &hints, &res);
    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(s, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    return 0;
}