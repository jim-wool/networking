# Beej's guide to Network Programming

source: https://beej.us/guide/bgnet/html/split/

# Socket programming in C on Linux - The Ultimate Guide for beginners

source: https://www.binarytides.com/socket-programming-c-linux-tutorial/

# Hands-On Network Programming with C

source: https://github.com/codeplea/Hands-On-Network-Programming-with-C


_________________________________________________________________________________

# Beej's guide:

"The OS should be as unobstrusive as possible and not require you to spend more money. The extra CPU power should be for apps, not for the OS"

## 1. What is a socket?

A way to speak to other programs using standard Unix file descriptors.
Everything in Unix is a file.
When Unix programs do any sort of I/O, they do it by reading or writing to a file descriptor, an integer associated with an open file. But, that file can be a network connection, a FIFO, a pipe, a terminal, a real file on the disk or just about anything else.
To get this file descriptor for network communication, we call the socket() system routine, we communicate through send() and recv() socket calls.
You can just use read() and write() but send() and recv() offer much greater control over data transmission.

## 2. Two types of internet sockets:
There are "Raw sockets", very powerful and i should look them up (todo)
The two types are "Stream sockets" and "Datagram sockets", which may hereafter be referred to as "SOCK_STREAM" and "SOCK_DGRAM". Datagram sockets are often called "connectionless".
Stream sockets are reliable two-way connected communication streams. They retain the order of the output (if i send 1, 2 they will arrive in the exact same order)
What uses stream sockets? telnet, ssh. All the characters that you type need to arrive in the same order you type them. Also HTTP uses them.
How do SOCK_STREAMs achieve this high level of data transmission? They use TCP/IP. IP deals primarily with Internet routing and is not generally responsible for data integrity. SOCK_DGRAMs use UDP
They're connectionless because you don't have to maintain an open conenction as you do with stream sockets. You just build a packet, slap an IP header on it with destination info and send it out. No connection needed. Used for multiplayer games, streaming audio...

Why would you use an unreliable underlying protocol (UDP)? Two reasons: speed and speed. It's way faster to fire and forget than it is to keep track of what has arrived safely and make sure it's in order and all that. If you're sending chat messages, TCP is great; if you're sending 40 positional updates per second, UDP is a good choice.

Data encapsulation: Ethernet[IP[UDP[TFTP[Data]]]]
When data is sent down the OSI stack, it's commonly described as:
Data -> Segment -> Packet -> Frame -> Bits

## 3. IP Addresses, structs, and Data Munging (changing data into another format)

### IP Addresses, versions 4 and 6:

Virtually every site on the Internet uses IPv4.
Forget this dots-and-numbers look of IPv4, too; now we've got a hexadecimal representation, with each two-byte chunk separated by a colon, like this:
2001:0db8:c9d2:aee5:73e3:934a:a5ae:9551
The address "::1" is the loopback address, it always means "this machine I'm running on now". In IPv4 it's 127.0.0.1
If you want to represent the IPv4 address 192.0.2.33 as an IPv6 address, you use the following notation: "::ffff:192.0.20.33"

### Port Numbers

It's a 16-bit number that's like the local address for the connection
Think of the IP address as the street address of a hotel, and the port number as the room number.
Say you want to have a computer that handles incoming mail AND web services - how do you differentiate between the two on a computer with a single IP address?

### Byte order

If you want to represent the two-byte hex number b34f, you'll store it in two sequential bytes b3 followed by 4f. This is called Big-Endian.
Little-Endian would store it like so: 4f followed by b3.

Endianness ensures that bytes in computer memory are read in a specific order.
- BE: stores the MSB first, this means that the first byte (at the lowest mem address) is the largest, which makes sense to those who read left to right.
- LE: stores the LSB first, this means that the first byte (at the lowest mem address) is the smallest, which makes sense to people who read right to left.

The issue of Endianness is most significant when it comes to communication.
How can you do this if you don't know the native Host Byte Order?
You just get to assume the Host Byte Order isn't right, and you always run the value through a function to set it to Network Byte order. The function will do the magic conversion IF it has to, and this way your code is portable to machines of differing endianness.

short (2 bytes), int (4 bytes), long (8 bytes)

The following functions work for the unsigned variations as well.
htons() -> h ost to n etwork s hort
ntohs() -> opposite
htonl() -> host to netowrk long
ntohl() -> opposite

Convert the numbers to Network Byte Order BEFORE they go out on the wire and convert them to Host Byte Order as they come in off the wire.

### Structs

- A socket descriptor is an int
The first struct we'll talk about is: struct addrinfo:
It's used to prep the socket address structures for subsequent use
Definition:
```c
struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    size_t ai_addrlen;
    struct sockaddr *ai_addr;
    char *ai_canonname;
    struct addrinfo *ai_next;
};
```

calling getaddresinfo() returns a new linked list of these structures filled out.

struct sockaddr holds socket address information for many types of sockets.

```c
struct sockaddr {
    unsigned short sa_family;
    char sa_data[14];
};
```
sa_family can be AF_INET (IPv4) or AF_INET6 (IPv6) for everything we do here. sa_data contains a dest address and a port number for the socket.
A better alternative is used for IPv4: struct sockaddr_in.

```c
struct sockaddr_in {
    short int sin_family;
    unsigned short int sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};
```

**sin_port must be in Network Byte Order using htons()**

```c
struct in_addr {
    uint32_t s_addr
};
```

```c
struct sockaddr_in6 {
    u_int16_t sin6_family;
    u_int16_t sin6_port;
    u_int16_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    u_int32_t sin6_scope_id;
};

struct in6_sockaddr {
    unsigned char s6_addr[16];
};
```

### IP Addresses, part two

If you have an IP address and you want to store it into a struct sockaddr_in or struct sockaddr_in6, use the inet_pton(AF_INET|AF_INET6, "IP address", &(sockaddr_var.sin_addr));
`pton` stands for "presentation to network"

example:
```c
struct sockaddr_in sa;
inet_pton(AF_INET, "192.168.0.1", &(sa.sin_addr)); // needs error checking obviously, check possible return values with man
```
We just converted string IPs into their binary representations bruh.

If we want to reverse this operation, we use the inet_ntop() function:
ntop stands for "network to printable"

```c
struct sockadd_in sa;
char buffer[INET_ADDSTRLEN];
ntop(AF_INET, &(sa.sin_addr), buffer, INET_ADDSTRLEN);
printf("%s\n", buffer);
```
NAT: network address translation: a process that translates internal IP addresses to external IP addresses.

## 5. Syscalls

The kernel takes over and does all the work for you in order to access the networking capabilities.

### getaddrinfo()

It helps set up the structs you need later on.

```c
int getaddrinfo(
    const char *node, // ex: www.example.com
    const char *service, // ex: "http" or port "80"
    const struct addrinfo *hints,
    struct addrinfo **res
)
```

The node param is the host name to connect to or an IP address.
hints point to a struct addrinfo that you've already filled out with relevant information.

AI_PASSIVE flag tells getaddrinfo() to assign the address of my local host to the socket structures

### socket() - get the file descriptor

```c
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
// ipv4 or ipv6, stream or dgram, tcp or upd
// getprotobyname()
```

domain can be PF_INET or PF_INET6, type can be SOCK_STREAM or SOCK_DGRAM.

What you really want to do is use the values from the results of the call to getaddrinfo() and feed them into socket() directly (using the res pointer)

```c
int status;
struct addrinfo hints, *res;
status = getaddrinfo("hostname", "http", &hints, &res);
int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)
```

s is socket descriptor that we can use in later syscalls, or -1 on error (check errno). It's not useful by itself.

### bind() - what port?

Once we have a socket, we might have to associate it with a port on the machine, this is commonly done if we want to listen() for incoming connections on a specific port. If we're just going to connect(), then we don't need the port.

```c
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
```

Sometimes rerunning a server might trigger a bind() failure, with the error that the address is already in use, meaning a little bit of the socket that was connected is still hanging around in the kernel, a workaround could be the following:

```c
int yes = 1;
setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))
```

### connect()

```c
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
```

### listen()

You want to wait for incoming connections and handle them in some way:

```c
int listen(int sockfd, int backlog);
```

backlog: the number of connections allowed on the incoming queue. Incoming connections will wait in this queue until we accept() them and this is the limit of how many we can queue.

You need to call bind() before calling listen() so that the server is running on a specific port.

```c
getaddrinfo();
socket();
bind();
listen();
freeaddrinfo();
```

### accept()

it returns a brand new socket fd to use for this single connection. Now you have 2 socket fds for the price of one (lmao idk why i copied this bit too). The original one is still listening for more new connections, the newly created one is ready to send() and recv().

```c
int new_fd = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
```

we will use the new_fd file descriptor for all send() and recv() calls. If you're only getting one single connection EVER, you can close() the listening sockfd in order to prevent more incoming connections on the same port.

### send() and recv()

these are used for communicating over stream sockets (connected). If you want to use regular unconnected datagram sockets you'll need sendto() and recvfrom().

The calls discussed in this section are blocking, meaning recv() will block until there is some data ready to receive (your program will stop on that syscall until someone sends you something, the OS is actually sleeping). send() can also block on rare occasions.

```c
int send(int sockfd, const void *msg, int len, int flags);
```

sockfd is the descriptor you want to send data to (from socket() or accept()). flags is usually set to 0 (see man page)

send() returns the number of bytes actually sent out. It might be less than the number you told it to send, so it trusts you to send the rest later. -1 is returned on error like every other goddamn syscall here and use errno.

```c
int recv(int sockfd, void *buf, int len, int flags);
```

recv() returns the number of bytes actually read into the buffer or -1 on error.

a 0 means that the remote side has closed the connection.

### sendto() and recvfrom(), DGRAM style

```c
int sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, socklen_t tolen);
```

to get our hands on the destination addr structn we'll probably either get it from getaddrinfo() or from recvfrom() or we'll fill it out by hand like the good boys we are.

same returns.

```c
int recvfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);
```

struct sockaddr_storage is a way to deal with both IPv4 and IPv6 because it's big enough for either.

### close() and shutdown()

```c
int close(int fd);
```

This will prevent any more reads and writes to the socket. Anyone attempting to read or write the socket on the remote end will receive an error.

shutdown() allows you to cut off communication in a certain direction or both ways:

```c
int shutdown(int sockfd, int how);
// how:
// 0: no more receives
// 1: no more sends
// 2: no more both
// returns 0 on success and -1 on error
```

### getpeername()

who are you?

```c
int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);
```

once we have the address we can use inet_ntop() or getnameinfo() or gethostbyaddr() to get more information. 

### gethostname()

who am I?

```c
int gethostname(char *hostname, size_t size);
```

hostname is where to store the actual name and size is the size of hostname.

## 6 Client-Server Background

Often there will only be one server on a machine and that server will handle multiple clients using fork(). The basic routine is the following:
server will wait for a connection, accept() it, and fork() a child process to handle it.

### Datagram sockets

**listener** sits on a machine waiting for an incoming packet on a port. **talker** sends a packet to that port, on the specified machine, that contains whatever the user enters on the command line. (an example bruh)

We're gonna tell the client and server to use specifically IPv6 to avoid the situation where the server is listening on IPv6 and the client sends on IPv4; The data simply would not be received

we don't need to listen() or accept() in this case.

https://beej.us/guide/bgnet/html/split/client-server-background.html