#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345

int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);

	/* Create socket */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

    /* Allow immediate reuse of the address*/
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	/* Bind socket to any address and port 12345 */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	/* Listen for incoming connections */
	if (listen(server_fd, 1) < 0)
	{
		perror("listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	/* Accept one connection */
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0)
	{
		perror("accept");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

	/* Clean up */
	close(client_fd);
	close(server_fd);

	return 0;
}
