#include "pipe_networking.h"
#include "game.h"

int to_server = -1;
int from_server = -1;
int EXIT = -1;
int endGameStatus = -1;

void handleSigInt() {
  if (to_server != -1) {
    write(to_server, &EXIT, sizeof(EXIT));
    close(to_server);
  }
  if (from_server != -1) {
    close(from_server);
  }
  printf("Game ended early.\n");
  exit(0);
}

void handleSigUSR1() {
  if (to_server != -1) {
    close(to_server);
  }
  if (from_server != -1) {
    close(from_server);
  }
  printf("The word was guessed.\n");
  exit(0);
}

void handleSigUSR2() {
  if (to_server != -1) {
    close(to_server);
  }
  if (from_server != -1) {
    close(from_server);
  }
  printf("You ran out of turns.\n");
  exit(0);
}

int main() {
  signal(SIGINT, handleSigInt);
  signal(SIGUSR1, handleSigUSR1);
  signal(SIGUSR2, handleSigUSR2);

  from_server = client_handshake( &to_server );

  int shmkey = -1;
  int semkey = -1;
  int gameID = -1;

  printf("client reading keys\n");

  read(from_server, &shmkey, sizeof(shmkey));
  read(from_server, &semkey, sizeof(semkey));
  read(from_server, &gameID, sizeof(int));

  printf("client received: shmkey = %d, semkey = %d\n", shmkey, semkey);

  pid_t pid = fork();
  if (pid == -1) {
    perror("client failed to fork");
    exit(1);
  }
  else if (pid != 0) {
    endGameStatus = runGame(semkey, shmkey, gameID);
    write(to_server, &endGameStatus, sizeof(int));
    if (endGameStatus == 1) kill(getpid(), SIGUSR1);
    if (endGameStatus == 2) kill(getpid(), SIGUSR2);
  }
  else {
    read(from_server, &endGameStatus, sizeof(endGameStatus));
    if (getppid() != 0) {
      if (endGameStatus == -1) kill(getppid(), SIGINT);
      if (endGameStatus == 1) kill(getppid(), SIGUSR1);
      if (endGameStatus == 2) kill(getppid(), SIGUSR2);
    }
    exit(0);
  }
}
