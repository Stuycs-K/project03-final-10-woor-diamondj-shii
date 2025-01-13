#include "pipe_networking.h"

int main() {
  signal(SIGINT, handle_sigint_server);
  signal(SIGPIPE, handle_sigpipe_server);

  int to_client1;
  int from_client1;

  int to_client2;
  int from_client2;

  srand(time(NULL));

  while (1) {
    from_client1 = server_setup();
    to_client1 = server_connect(from_client1);
    from_client2 = server_setup();
    to_client2 = server_connect(from_client2);

    pid_t f = fork();
    printf("forking\n");
    if (f == -1) {
      printf("fork failed\n");
      exit(EXIT_FAILURE);
    }
    if (f) { // parent
      close(from_client1);
      close(from_client2);
      close(to_client1);
      close(to_client2);
    }
    else { // child
      //write(to_client1, *GO, sizeof(GO));
      
    }
  }
}
