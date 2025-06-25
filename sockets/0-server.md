#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345

/*
 * main - Entry point of the server program
 *
 * Creates IPv4 TCP socket, binds it to port 12345,
 * listens for incoming connections, and blocks
 *
 * Return: Always 0 success, exits on failure
*/

int main(void)
{
	int server_fd;
	struct sockaddr_in address;

    /* Create socket file descriptor IPv4*/
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    /*Avoid bind fail*/
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
    /*Prepare sockaddr_in structure*/
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    /*Bind*/
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    /*Listen*/
    if (listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d\n", PORT);

    /*Hang indefinitely*/
    while (1)
        pause();

    close(server_fd);
    return 0;
}