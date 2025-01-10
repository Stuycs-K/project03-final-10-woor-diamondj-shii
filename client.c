#include "pipe_networking.h"
#include "game.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  int shmkey = -1;
  int semkey = -1;

  read(from_server, &shmkey, sizeof(shmkey));
  read(from_server, &semkey, sizeof(semkey));

  runGame(semkey, shmkey);
}
