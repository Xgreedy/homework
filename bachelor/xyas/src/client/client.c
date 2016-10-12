/*
 *  src/client/client.c
 *
 *  Harry Wei <harryxiyou@gmail.com> (C) 2011
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "xyas.h"
#include <gtk/gtk.h>

#define BUFFSIZE 100

void Die(char *mess) { perror(mess); exit(1); }

void xyas_client(void) {
	//printf("argc is %d\n", argc);
	//printf("argv[0] is %s, argv[1] is %s, argv[2] is %s", _argv[0], _argv[1], _argv[2]);
	int sock;
	struct sockaddr_in echoserver;
	char buffer[BUFFSIZE];
	unsigned int echolen;
	int received = 0;
   
	memset(buffer, 0, BUFFSIZE);
	/* Create the TCP socket */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		Die("Failed to create socket");
	}
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
	echoserver.sin_family = AF_INET;                  /* Internet/IP */
	echoserver.sin_addr.s_addr = inet_addr(ip);  /* IP address */
	echoserver.sin_port = htons(port);       /* server port */
	/* Establish connection */
	if (connect(sock,
				(struct sockaddr *) &echoserver,
				sizeof(echoserver)) < 0) {
		Die("Failed to connect with server");
	}
	int i = get_buff();
	if (0 == i) { //add
		g_message("This is add branch!");
		g_message("algo_name is %s", get_text[i]);
		char *tmp_text = g_strdup(get_text[i]);
		memset(buffer, 0, BUFFSIZE);
#if 0
		add_text = gtk_text_new(NULL, NULL);
		gtk_text_set_editable(add_text, TRUE);
		gtk_container_add(GTK_CONTAINER (add_window), add_text);
#endif
		create_add_window();
		//gtk_widget_show_all(GTK_WIDGET (add_window));
		//gtk_main();
		g_message("num is [%d], algo_name is [%s], text is [%s]", i, tmp_text, add_text);
		snprintf(buffer, BUFFSIZE, "%d %s %s", i, get_text[i], add_text);
		g_message("buffer is %s", buffer);
		if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
			Die("Mismatch in number of sent bytes");
		}
	} else if (1 == i) { //delete
		g_message("This is delete branch!");
//		echolen = strlen(get_text[i]);
//		printf("len is %d\n", echolen);
		sprintf(buffer, "%d %s", i, get_text[i]);
//		echolen += 2;
		if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
			Die("Mismatch in number of sent bytes");
		}
//		printf("len is %d\n", echolen);
	} else if (2 == i) { //alter
		g_message("This is alter branch!");
		int bytes = 0;
		sprintf(buffer, "%d %s", i, get_text[i]);
		if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
			Die("Mismatch in number of sent bytes");
		}
#if 0
		memset(buffer, BUFFSIZE, 0);
		if ((bytes = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
			Die("Failed to receive bytes from server");
		}
		printf("alter buffer is [%s]\n", buffer);
#endif
		create_alter_window();
		g_message("alter text is [%s]", alter_text);
		memset(buffer, BUFFSIZE, 0);
		sprintf(buffer, "%s", alter_text);
		if (send(sock, buffer, BUFFSIZE, 0) != BUFFSIZE) {
			Die("Mismatch in number of sent bytes");
		}
	} else if (3 == i) { //search
		/* Send the word to the server */
		g_message("This is search branch!");
		echolen = strlen(get_text[i]);
		printf("len is %d\n", echolen);
		sprintf(buffer, "%d %s", i, get_text[i]);
		echolen += 2;
		if (send(sock, buffer, echolen, 0) != echolen) {
			Die("Mismatch in number of sent bytes");
		}
		printf("len is %d\n", echolen);
		/* Receive the word back from the server */
		fprintf(stdout, "Received >>>>>>>>>>>>>\n");
		while (received < echolen) {
			int bytes = 0;
			if ((bytes = recv(sock, buffer, BUFFSIZE, 0)) < 1) {
				Die("Failed to receive bytes from server");
			}
			received += bytes;
			buffer[bytes] = '\0';        /* Assure null terminated string */
#if 1
			if (0 == g_strcmp0(buffer, "nothing")) {
				g_message("we have not find your algorithm!");
				print_error();
				goto out;
			}
#endif
		}
		fprintf(stdout, "buffer is %s", buffer);
		create_algo_window();
		gtk_label_set_text(GTK_LABEL (algo_label), buffer);
		gtk_widget_show_all(GTK_WIDGET (algo_window));
		gtk_main();
		fprintf(stdout, "\n");
	} else {
		g_message("There is no this function!");
		exit(1);
	}
out:
	close(sock);
	return ;
	//exit(0);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "USAGE: client <server_ip> <port>\n");
		exit(1);
	}
	port = atoi(argv[2]);
	sprintf(ip, "%s", argv[1]);
	gtk_init(&argc, &argv);
	create_window();
	gtk_widget_show_all(GTK_WIDGET (window));
	g_signal_connect(G_OBJECT (submit_button), "clicked", G_CALLBACK (xyas_client), NULL);
	gtk_main();
	return 0;
}
