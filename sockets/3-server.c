#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received;

	/* Create socket */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Allow address reuse */
	int opt = 1;
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	/* Prepare server address */
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

	if (listen(server_fd, 1) < 0)
	{
		perror("listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0)
	{
		perror("accept");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

	bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_received < 0)
	{
		perror("recv");
		close(client_fd);
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	buffer[bytes_received] = '\0'; /* Null-terminate the received message */
	printf("Message received: \"%s\"\n", buffer);

	close(client_fd);
	close(server_fd);
	return (0);
}
