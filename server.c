#include "pipe_networking.h"
#include "control.h"

int main() {
  signal(SIGINT, handle_sigint_server);
  signal(SIGPIPE, handle_sigpipe_server);

  printf("server opened\n");

  int to_client1;
  int from_client1;

  int to_client2;
  int from_client2;

  srand(time(NULL));

  while (1) {
//    int numClients = 0;

    from_client1 = server_setup();
    to_client1 = server_connect(from_client1);
//    numClients++;
    from_client2 = server_setup();
    to_client2 = server_connect(from_client2);
//    numClients++;

//     while (numClients < 2) {
//       to_client1 = to_client2;
//       from_client1 = from_client2;
//       from_client2 = server_setup();
//       to_client2 = server_connect(from_client2);
//       numClients++;
//     }

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
      int * shmkey = (int*) malloc(sizeof(int));
      int * semkey = (int*) malloc(sizeof(int));
      int fd = open("/dev/random", O_RDONLY);
      int gameID = getpid();

      read(fd, shmkey, sizeof(int));
      read(fd, semkey, sizeof(int));
      *shmkey = (*shmkey < 0 ? (*shmkey * -1) : *shmkey) % 100000;
      *semkey = (*semkey < 0 ? (*semkey * -1) : *semkey) % 100000;

      gameSetup(*shmkey, *semkey, gameID);

      write(to_client1, shmkey, sizeof(int));
      write(to_client2, shmkey, sizeof(int));

      write(to_client1, semkey, sizeof(int));
      write(to_client2, semkey, sizeof(int));

      write(to_client1, &gameID, sizeof(int));
      write(to_client2, &gameID, sizeof(int));

      printf("[subserver] game setup: gameID = %d, shmkey = %d, semkey = %d\n", gameID, *shmkey, *semkey);

      fd_set fds;
      FD_ZERO(&fds);
      FD_SET(from_client1, &fds);
      FD_SET(from_client2, &fds);
      select((to_client1 > to_client2 ? to_client1 : to_client2) + 1, &fds, NULL, NULL, NULL);

      if(FD_ISSET(from_client1, &fds)) {
        int gameStatus;
        read(from_client1, &gameStatus, sizeof(gameStatus));
        write(to_client2, &gameStatus, sizeof(gameStatus));
        reset(*shmkey, *semkey, gameID);
        exit(0);
      }
      if(FD_ISSET(from_client2, &fds)) {
        int gameStatus;
        read(from_client2, &gameStatus, sizeof(gameStatus));
        write(to_client1, &gameStatus, sizeof(gameStatus));
        reset(*shmkey, *semkey, gameID);
        exit(0);
      }
    }
  }
}
