#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

/**
 * main - Entry point for an HTTP server
 *
 * Listens for IPv4 TCP connections on port 8080,
 * prints the client's IP, full HTTP request, and the first line breakdown.
 * Afterward sends a basic HTTP 200 OK response and loops for the next client.
 *
 * Return: Always 0 (Success)
 */

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

	/* Allow immediate reuse of the address */
	int opt = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	/* Initialize server address structure */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	/* Bind the socket to the address and port */
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	/* Listen for incoming connections */
	if (listen(server_fd, 5) < 0)
	{
		perror("listen");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	while (1)
	{
		/* Accept a new client connection */
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		if (client_fd < 0)
		{
			perror("accept");
			continue;
		}

		printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

		/* Receive HTTP request */
		bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
		if (bytes_received <= 0)
		{
			perror("recv");
			close(client_fd);
			continue;
		}
		buffer[bytes_received] = '\0';

		/* Print the raw HTTP request */
		printf("Raw request: \"%s\"\n", buffer);

		/*Parse the first line of the HTTP request*/
		char method[16], path[256], version[32];
		sscanf(buffer, "%15s %255s %31s", method, path, version);
		printf("Method: %s\n", method);
		printf("Path: %s\n", path);
		printf("Version: %s\n", version);

		/* Send HTTP response */
		const char *response = "HTTP/1.1 200 OK\r\n\r\n";
		send(client_fd, response, strlen(response), 0);

		close(client_fd);
	}

	close(server_fd);
	return 0;
}
