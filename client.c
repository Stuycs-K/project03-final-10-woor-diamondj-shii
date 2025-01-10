#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  printf("client: to_server: %d\n", to_server);
  printf("client: from_server: %d\n", from_server);
}
