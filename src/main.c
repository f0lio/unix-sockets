
#include "server.h"

int main(int argc, char const *argv[])
{    
    if (argc != 2)
    {
        printf("Usage: ./server port\n");
        return 1;
    }

    int port = atoi(argv[1]);
    if (port <= 0)
    {
        fprintf(stderr, "Invalid port\n");
        return 1;
    }
    
    {
        // look at /etc/services
        struct servent *s = getservbyport(htons(port), DEFAULT_PROTOCOL);
        if (s != NULL)
            printf("Service: %s\n", s->s_name), SEP;
    }

    t_server *server = new_server(AF_INET, SOCK_STREAM, 0, port, DEFAULT_BACKLOG);

    server->new_socket(server);
    server->listen(server, true);

    return 0;
}
