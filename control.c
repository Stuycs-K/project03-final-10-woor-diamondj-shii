#include "control.h"

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

char * generateRandomWord() {
  FILE * file = fopen("valid_answers.txt", "r");
  srand(time(NULL));
  int targetWord = rand() % TOTAL_ANSWERS;
  char * word = malloc(8);

  int i = 1;
  while (fgets(word, 8, file)) {
    if (i == targetWord) {
      fclose(file);
      break;
    }
    i++;

    if (i > TOTAL_ANSWERS) {
      printf("error: target word not found\n");
      exit(1);
    }
  }
  printf("target word: %d\n", targetWord);
  
  return word;
}

void gameSetup() {
  // create semaphore w/ value 1
  int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  union semun us;
  us.val = 1;
  semctl(semd, 0, SETVAL, us);

  // create guess file
  open("guesses.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  chmod("guesses.txt", 0666);
}

void reset() {
  // remove semaphore
  int semd = semget(KEY, 1, IPC_STAT);
  semctl(semd, 1, IPC_RMID);

  // remove guess file
  remove("guesses.txt");
}
