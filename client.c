#include "pipe_networking.h"
#include "game.h"

int to_server = -1;
int from_server = -1;
int EXIT = -1;

void handleSigInt() {
  if (to_server != -1) {
    write(to_server, &EXIT, sizeof(EXIT));
    close(to_server);
  }
  if (from_server != -1) {
    close(from_server);
  }
  exit(0);
}

void handleSigUSR1() {
  if (to_server != -1) {
    close(to_server);
  }
  if (from_server != -1) {
    close(from_server);
  }
  printf("other client exited\n");
  exit(0);
}

int main() {
  signal(SIGINT, handleSigInt);

  from_server = client_handshake( &to_server );

  int shmkey = -1;
  int semkey = -1;
  pid_t server_pid = -1;

  read(from_server, &shmkey, sizeof(shmkey));
  read(from_server, &semkey, sizeof(semkey));

  printf("client received: shmkey = %d, semkey = %d\n", shmkey, semkey);

  pid_t pid = fork();
  if (pid == -1) {
    perror("client failed to fork");
    exit(1);
  }
  else if (pid != 0) {
    runGame(semkey, shmkey);
  }
  else {
    int buffer[1];
    read(from_server, buffer, sizeof(buffer));
    kill(getppid(), SIGUSR1);
    exit(0);
  }
}
