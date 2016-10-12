/*
 * src/server/server.c
 *
 * Harry Wei <harryxiyou@gmail.com> (C) 2011
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <glib.h>

#include "sqlite3.h"
#include "xyas_sqlite.h"

#define MAXPENDING 5    /* Max connection requests */
#define BUFFSIZE 100
void Die(char *mess) { perror(mess); exit(1); }

static void 
HandleClient(int sock, 
			struct xyas_ctrl *ctrl,
			struct xyas_algo *algo_item) {
	char buffer[BUFFSIZE];
	int received = -1;
	int ret = 0;

	memset(buffer, 0, BUFFSIZE);
	/* Receive message */
	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
		Die("Failed to receive initial bytes from client");
	}
	printf("buffer is %s\n", buffer);
	gchar **v = NULL;
	v = g_strsplit(buffer, " ", 2);
	char *endptr = NULL;
	int num = strtoul(v[0], &endptr, 0);
	printf("num is %d, str is %s\n", num, v[1]);
	if (0 == num) { //add algorithm
		printf("add algorithm\n");
		gchar **v1 = g_strsplit(v[1], " ", 2);
		struct xyas_algo add_algo;
		memset(&add_algo, 0, sizeof(struct xyas_algo));
		sprintf(add_algo.algo_name, "%s", v1[0]);
		add_algo.ctime = 1;
		add_algo.lmtime = 2;
		sprintf(add_algo.author, "%s", "jiawei");
		snprintf(add_algo.text, TEXT_LEN, "%s", v1[1]);
		if (-1 == xyas_insert_2sqlite(ctrl, &add_algo)) {
			g_message("insert 2 sqlite error!");
			exit(1);
		}
	} else if (1 == num) { //delete algorithm
		printf("delete algorithm\n");
		memset(buffer, 0, BUFFSIZE);
		sprintf(buffer, "%s", v[1]);
#if 0
		if (send(sock, buffer, BUFFSIZE - 1, 0) != BUFFSIZE - 1) {
			Die("Failed to send bytes to client");
		}
#endif
		g_message("buffer is %s", buffer);
		if (-1 == xyas_delete_sqlite_item(ctrl, buffer)) {
			g_message("xyas delete sqlite item error!");
			exit(1);
		}
	} else if (2 == num) { //alter algorithm
		g_message("alter algorithm\n");
		memset(buffer, 0, BUFFSIZE);
		sprintf(buffer, "%s", v[1]);
		if (-1 == (ret = xyas_search_sqlite_item(ctrl, buffer, algo_item))) {
			g_message("xyas search sqlite error!");
		}
		if (-1 == xyas_delete_sqlite_item(ctrl, algo_item->algo_name)) {
			g_message("xyas delete sqlite item error!");
			exit(1);
		}
		memset(algo_item->text, 0, TEXT_LEN);
		if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
			Die("Failed to receive initial bytes from client");
		}
		sprintf(algo_item->text, "%s", buffer);
		if (-1 == xyas_insert_2sqlite(ctrl, algo_item)) {
			g_message("insert 2 sqlite error!");
			exit(1);
		}
#if 0
		sprintf(buffer, "%s", algo_item->text);
		if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
			Die("Failed to send bytes to client");
		}
		printf("alter algorithm\n");
		memset(buffer, 0, BUFFSIZE);
		sprintf(buffer, "%s", "alter");
		if (send(sock, buffer, BUFFSIZE - 1, 0) != BUFFSIZE - 1) {
			Die("Failed to send bytes to client");
		}
#endif
	} else if (3 == num) { //search algorithm
		printf("search algorithm\n");
		sprintf(buffer, "%s", v[1]);
		if (-1 == (ret = xyas_search_sqlite_item(ctrl, buffer, algo_item))) {
			g_message("xyas search sqlite error!");
		}
		g_message("ret is %d", ret);
		sprintf(buffer, "%s", algo_item->text);
		printf("received name is %s\n", buffer);
		printf("text is %s\n", algo_item->text);
#if 1
		if (0 == ret) {
			memset(buffer, 0, BUFFSIZE);
			g_message("we have not find your algorithm!");
			sprintf(buffer, "%s", "nothing");
			ret = 1;
		}
#endif
		/* Send bytes and check for more incoming data in loop */
//		while (received > 0) {
			/* Send back received data */
			if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
				Die("Failed to send bytes to client");
			}

#if 0
			/* Check for more data */
			if ((received = recv(sock, buffer, BUFFSIZE - 1, 0)) < 0) {
				Die("Failed to receive additional bytes from client");
			}
			ret = 0;
			if (-1 == (ret = xyas_search_sqlite_item(ctrl, buffer, algo_item))) {
				g_message("xyas search sqlite error!");
			}
			if (0 == ret) {
				g_message("we didn't find your algorithm");
			}
#endif
//		}
	} 
out:
#if 0
	if (ret == 1) {
		sleep(2);
	}
#endif
	close(sock);
	return ;
}

int main(int argc, char *argv[]) {
	int serversock, clientsock;
	struct sockaddr_in echoserver, echoclient;
	const char *uri = "/tmp/testdb";
	const char *db = "xyas.db";
	struct xyas_algo algo_item;
	struct xyas_ctrl *ctrl = NULL;

	ctrl = xyas_init_sqlite(uri, db);
	if (NULL == ctrl) {
		g_message("xyas init sqlite error!");
		exit(1);
	}
	memset(&algo_item, 0, sizeof(struct xyas_algo));
	if (argc != 2) {
		fprintf(stderr, "USAGE: echoserver <port>\n");
		exit(1);
	}
#if 0
	struct xyas_algo _algo_item = {
		.algo_name = "1.c",
		.ctime = 1,
		.lmtime = 2,
		.author = "jiawei",
		.text = "This is 1.c",
	};
	if (-1 == xyas_insert_2sqlite(ctrl, &_algo_item)) {
		g_message("xyas insert 2 sqlite error!");
	}
#endif
	/* Create the TCP socket */
	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		Die("Failed to create socket");
	}
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
	echoserver.sin_family = AF_INET;                  /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Incoming addr */
	echoserver.sin_port = htons(atoi(argv[1]));       /* server port */
	/* Bind the server socket */
	if (bind(serversock, (struct sockaddr *) &echoserver,
				sizeof(echoserver)) < 0) {
		Die("Failed to bind the server socket");
	}
	/* Listen on the server socket */
	if (listen(serversock, MAXPENDING) < 0) {
		Die("Failed to listen on server socket");
	}
	/* Run until cancelled */
	while (1) {
		unsigned int clientlen = sizeof(echoclient);
		/* Wait for client connection */
		if ((clientsock =
					accept(serversock, (struct sockaddr *) &echoclient,
						&clientlen)) < 0) {
			Die("Failed to accept client connection");
		}
		fprintf(stdout, "Client connected: %s\n",
				inet_ntoa(echoclient.sin_addr));
		HandleClient(clientsock, ctrl, &algo_item);
	}
}
