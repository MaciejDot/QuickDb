#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include "hash_table.h"
#include "alloc-functions.h"
#define MAX 200
#define PORT 8080
#define SA struct sockaddr
hash_table *tab;
// Function designed for chat between client and server.
void *func(void *sock)
{
	int sockfd = *(int *)sock;
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;)
	{
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("before: %s\n", get_operation(tab, "key", 4)->data);
		add_operation(tab, "key", 4, buff, MAX);
		printf("after: %s\n", get_operation(tab, "key", 4)->data);
		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
			;

		// and send that buffer to client
		write(sockfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main()
{
	tab = _malloc(sizeof *tab);
	hash_table_init(tab, 1024 * 1024);
	printf("start\n ");
	add_operation(tab, "key", 4, "value", 6);
	int sockfd, len;
		struct sockaddr_in servaddr, cli;

		// socket create and verification
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));

		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(PORT);

		// Binding newly created socket to given IP and verification
		(bind(sockfd, (SA *)&servaddr, sizeof(servaddr)));

		// Now server is ready to listen and verification
		listen(sockfd, 5);
	for (;;)
	{
		printf("wait\n");
		int *confd = (int*)_malloc(sizeof*confd);
		len = sizeof(cli);
		*confd = accept(sockfd, (SA *)&cli, &len);
		pthread_t inc_x_thread;
		pthread_create(&inc_x_thread, NULL, func, (void *)confd);
		//pthread_join(inc_x_thread, NULL);
	}
	// After chatting close the socket
	//close(sockfd);
}