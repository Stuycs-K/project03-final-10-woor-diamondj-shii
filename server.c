#include <signal.h>

#include "pipe_networking.h"

int main() {
  signal(SIGINT, handle_sigint_server);
  signal(SIGPIPE, handle_sigpipe_server);

  int to_client1;
  int from_client1;

  int to_client2;
  int frmo_client2;

  while (1) {
    from_client1 = server_setup();
    to_client1 = server_connect(from_client1);
    from_client2 = server_setup();
    to_client2 = server_connect(from_client2);

    pid_t f = fork();
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
      int * shmkey = malloc(sizeof(int));
      int * semkey = malloc(sizeof(int));
      int fd = open("/dev/random", O_RDONLY);
      read(fd, shmkey, sizeof(int));
      read(fd, semkey, sizeof(int));

      gameSetup(*shmkey, *semkey);

      write(to_client1, *shmkey, sizeof(shmkey));
      write(to_client2, *shmkey, sizeof(shmkey));

      write(to_client1, *semkey, sizeof(semkey));
      write(to_client2, *semkey, sizeof(semkey));
    }
  }
}
