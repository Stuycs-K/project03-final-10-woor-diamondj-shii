#include "control.h"

#define SEMKEY 826534
#define SHMKEY 98195187

union semun {
  int val;
  struct semid_ds* buf;
  unsigned short* array;
  struct seminfo *__buf;
};

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("no args provided\n");
    exit(1);
  }
  if (strcmp(argv[1], "setup") == 0) gameSetup();
  if (strcmp(argv[1], "reset") == 0) reset();
}

void gameSetup() {
  // create semaphore w/ value 1
  int semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  union semun us;
  us.val = 1;
  semctl(semd, 0, SETVAL, us);

  // create guess file
  open("guesses.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  chmod("guesses.txt", 0666);

  // generate answer
  // generateRandomWord()

  // create shared memory
  int shmid = shmget(SHMKEY, 6 * sizeof(char), IPC_CREAT | 0666);
  char* answer = (char*) shmat(shmid, 0, 0);
  strcpy(answer, "hello");
  shmdt(answer);
}

void reset() {
  // remove semaphore
  int semd = semget(SEMKEY, 1, IPC_STAT);
  semctl(semd, 1, IPC_RMID);

  // remove guess file
  remove("guesses.txt");
}
