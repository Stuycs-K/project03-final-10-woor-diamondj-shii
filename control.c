#include "control.h"

#define BUFFERSIZE 200
#define SEMKEY 826534
#define TURNSHMKEY 712021529
#define ANSWERSHMKEY 98195187
#define GUESSARRAYSHMKEY 1556200266

char* generateRandomWord() {
  FILE * file = fopen("valid_answers.txt", "r");
  srand(time(NULL));
  int targetWord = rand() % TOTAL_ANSWERS;
  char word[8];

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

  char * shortenedWord = malloc(6);
  strncpy(shortenedWord, word, 5);
  shortenedWord[5] = '\0';

  return shortenedWord;
}

void gameSetup(int shmkey, int semkey) {
  // create semaphore w/ value 1
  int semd = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0644);
  union semun us;
  us.val = 1;
  semctl(semd, 0, SETVAL, us);

  // create guess file
  open("guesses.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  chmod("guesses.txt", 0666);

  // generate answer
  char* word = generateRandomWord();
  printf("word: %s\n", word);

  // create shared memory
  int shmid;
  //store turn
  shmid = shmget(TURNSHMKEY, sizeof(int), IPC_CREAT | 0666);
  int* turn = shmat(shmid, 0, 0);
  *turn = 0;
  shmdt(turn);
  //store guessArray
  shmid = shmget(GUESSARRAYSHMKEY, BUFFERSIZE, IPC_CREAT | 0666);
  char** guessArray = (char**) shmat(shmid, 0, 0);
  for (int i = 0; i < 6; i++){
    guessArray[i] = malloc(BUFFERSIZE);
  }
  shmdt(guessArray);
  //store answer
  shmid = shmget(ANSWERSHMKEY, 6 * sizeof(char), IPC_CREAT | 0666);
  char* answer = (char*) shmat(shmid, 0, 0);
  strcpy(answer, word);
  shmdt(answer);
}

void reset(int shmkey, int semkey) {
  // remove semaphore
  int semd = semget(semkey, 1, IPC_STAT);
  semctl(semd, 1, IPC_RMID);

  // remove guess file
  remove("guesses.txt");

  // remove shared memory
  int shmid = shmget(ANSWERSHMKEY, 0, 0);
  shmctl(shmid, IPC_RMID, 0);
}
