#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  if (access(WKP, F_OK) != -1) {
    if (unlink(WKP) == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("server: removed old fifo\n");
  }

  if (mkfifo(WKP, 0666) == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("server: made fifo\n");

  printf("server: opening wkp, waiting for client\n");
  int upstream = open(WKP, O_RDONLY);
  printf("server: client connected to wkp\n");

  if(unlink(WKP) == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  return upstream;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();
  printf("server has been setup\n");

  char to_client_string[HANDSHAKE_BUFFER_SIZE]; // also the pid of the child process
  read(from_client, &to_client_string, HANDSHAKE_BUFFER_SIZE);

  *to_client = open(to_client_string, O_WRONLY);
  srand(time(NULL));
  int SYN_ACK = rand();
  write(*to_client, &SYN_ACK, sizeof(SYN_ACK));

  int ACK_RECIEVED = -1;
  read(from_client, &ACK_RECIEVED, sizeof(ACK_RECIEVED));
  if (ACK_RECIEVED != SYN_ACK + 1) {
    char error[100];
    sprintf(error, "ACK not recieved correctly (SYN_ACK = %d, ACK = %d\n", SYN_ACK, ACK_RECIEVED);
    perror(error);
    exit(EXIT_FAILURE);
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int pid = getpid();
  char PP[15];
  sprintf(PP, "%d", pid);
  
  if (access(PP, F_OK) != -1) {
    if (unlink(PP) == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    printf("client: removed old PP\n");
  }

  if (mkfifo(PP, 0666) == -1) {
    printf("Error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("client: made PP\n");

  printf("client: opening wkp, unblocking server\n");
  *to_server = open(WKP, O_WRONLY);
  write(*to_server, PP, strlen(PP) + 1);
  printf("client: sent PP to server\n");

  printf("client: waiting for SYN_ACK\n");
  int downstream = open(PP, O_RDONLY);
  int SYN_ACK_RECIEVED = 0;
  read(downstream, &SYN_ACK_RECIEVED, sizeof(SYN_ACK_RECIEVED));

  printf("client: recieved SYN_ACK: %d\n", SYN_ACK_RECIEVED);

  int ACK = SYN_ACK_RECIEVED + 1;

  write(*to_server, &ACK, sizeof(ACK));

  unlink(PP);

  return downstream;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  char to_client_string[HANDSHAKE_BUFFER_SIZE]; // also the pid of the child process
  read(from_client, &to_client_string, HANDSHAKE_BUFFER_SIZE);

  int to_client = open(to_client_string, O_WRONLY);
  srand(time(NULL));
  int SYN_ACK = rand();
  write(to_client, &SYN_ACK, sizeof(SYN_ACK));

  int ACK_RECIEVED = -1;
  read(from_client, &ACK_RECIEVED, sizeof(ACK_RECIEVED));
  if (ACK_RECIEVED != SYN_ACK + 1) {
    char error[100];
    sprintf(error, "ACK not recieved correctly (SYN_ACK = %d, ACK = %d\n", SYN_ACK, ACK_RECIEVED);
    perror(error);
    exit(EXIT_FAILURE);
  }

  return to_client;
}

void handle_sigint_server() {
  unlink(WKP);
  exit(0);
}

void handle_sigpipe_server() {
  printf("client disconnected\n");
}

