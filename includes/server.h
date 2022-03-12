#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netinet/in.h>
#include <netdb.h>

// #include <sys/socket.h>

#define DEFAULT_PROTOCOL    "tcp"
#define DEFAULT_BACKLOG     5

#define BUFFER_SIZE 1024 // buffer size for reading and writing data from/to client

#define SEP write(1, "---\n", 4);

#undef true
#undef false
#define true 1
#define false 0
typedef char bool;

typedef struct s_server
{
    // server data
    int         service;
    int         protocol;
    int         domain;
    uint16_t    port;
    int         backlog; // number of connection requests that will be queued before further requests are refused
    int         sockfd;
    
    struct
    sockaddr_in address;
    
    // client data
    int         client_sock;
    struct
    sockaddr_in client_addr;

    void (*new_socket)(struct s_server *);
    void (*listen)(struct s_server *, bool);

} t_server;

t_server    *new_server(int domain, int service, int protocol, u_int16_t port, int backlog);
void        _server_new_socket(t_server *this);
void        _server_listen(t_server *this, bool show_msg);

#endif