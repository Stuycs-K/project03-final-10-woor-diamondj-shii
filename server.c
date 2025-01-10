#include <signal.h>

#include "pipe_networking.h"

int main() {
  signal(SIGINT, handle_sigint_server);
  signal(SIGPIPE, handle_sigpipe_server);

  int to_client;
  int from_client;

  while (1) {
    from_client = server_setup();
    pid_t f = fork();
    if (f == -1) {
      printf("fork failed\n");
      exit(EXIT_FAILURE);
    }
    if (f) {
      close(from_client);
    }
    else {
      to_client = server_connect(from_client);
      while (1) {
        int value = rand() % 101;
        if (write(to_client, &value, sizeof(value)) == -1) {
          printf("subserver: failed to send value, closing subserver\n");
          close(to_client);
          close(from_client);
          exit(0);
        }
        else {
          printf("subserver: sent %d\n", value);
          sleep(1);
        }
      }
    }
  }
}
