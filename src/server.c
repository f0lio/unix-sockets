
#include "server.h"

t_server    *new_server(int domain, int service, int protocol, u_int16_t port, int backlog)
{
    t_server *server = malloc(sizeof(t_server));
    
    if (server == NULL)
        return (NULL);

    server->sockfd = 0;
    server->client_sock = 0;
    
    
    server->protocol = protocol;
    server->domain = domain;
    server->port = port;
    server->service = service;
    server->backlog = backlog;

    bzero(&server->address, sizeof(server->address));
    
    server->address.sin_family = domain;
    server->address.sin_port = htons(port);
    server->address.sin_addr.s_addr = INADDR_ANY;
    
    server->new_socket = _server_new_socket;
    server->listen = _server_listen;
    return (server);
}

void _server_new_socket(t_server *this)
{
    this->sockfd = socket(this->domain, this->service, this->protocol);
    
    if (this->sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    if (bind(this->sockfd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0)
    {
        perror("bind");
        exit(1);
    }
}

void        _server_listen(t_server *this, bool show_msg)
{
    // Listen for incoming connections
    if (listen(this->sockfd, this->backlog) < 0)
    {
        perror("listen");
        exit(1);
    }

    if (show_msg)
        printf("Server running on port %d\n", this->port), SEP;

    // Accept connection from an incoming client
    int     addrlen = sizeof(this->client_addr);
    char    buffer[BUFFER_SIZE];
    int     read_size;
    
    while (1)
    {
        this->client_sock = accept(
            this->sockfd,(struct sockaddr *)&this->client_addr, &addrlen);

        if (this->client_sock < 0)
        {
            perror("accept");
            exit(1);
        }
        
        bzero(buffer, BUFFER_SIZE);
        read_size = read(this->client_sock, buffer, BUFFER_SIZE - 1);
        
        if (read_size < 0)
        {
            perror("read");
            exit(1);
        }

        printf("Received: %s\n", buffer);
        read_size = write(this->client_sock, buffer, strlen(buffer));
        
        if (read_size < 0)
        {
            perror("write");
            exit(1);
        }
        close(this->client_sock);
    }
}