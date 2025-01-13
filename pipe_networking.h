#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

#ifndef NETWORKING_H
#define NETWORKING_H
#define WKP "mario"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100

#define READ 0
#define WRITE 1

int server_handshake(int *to_client);
int client_handshake(int *to_server);

//for basic & persistent servers
int server_connect(int from_client);

//for forking server
int server_setup();

//multi_server
int multi_server_setup();
// int multi_server_connect(int from_client, struct message m);

void handle_sigint_server();
void handle_sigpipe_server();

#endif
