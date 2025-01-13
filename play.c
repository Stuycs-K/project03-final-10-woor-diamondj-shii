#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "game.h"

#define BUFFERSIZE 200
#define SEMKEY 826534
#define TURNSHMKEY 712021529
#define ANSWERSHMKEY 98195187
#define GUESSARRAYSHMKEY 1556200266

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main() {
  //initialize global variables
  int* turn = (int*) malloc(sizeof(int));
  char* answer = (char*) malloc(6 * sizeof(char));
  char** guessArray = (char**) malloc(6 * BUFFERSIZE);
  for (int i = 0; i < 6; i++){
    guessArray[i] = malloc(BUFFERSIZE);
  }
  while (1) {
    // wait to access semaphore
    printf("waiting for turn...\n");
    int semd = semget(SEMKEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    // decrement semaphore once accessed
    semop(semd, &sb, 1);
    // accessing shared data
    int shmid;
    //access int turn
    shmid = shmget(TURNSHMKEY, sizeof(int), IPC_CREAT | 0666);
    turn = shmat(shmid, 0, 0);
    //access char* answer
    shmid = shmget(ANSWERSHMKEY, 0, 0);
    answer = shmat(shmid, 0, 0);
    //access char** guessArray
    shmid = shmget(GUESSARRAYSHMKEY, BUFFERSIZE * 6, IPC_CREAT | 0666);
    guessArray = (char**) shmat(shmid, 0, 0);
    // making turn
    printBoard(guessArray, *turn);
    char buffer[BUFFERSIZE] = {'\0'};
    printf("Enter a 5-letter word\n");
    fgets(buffer, BUFFERSIZE, stdin);
    checkGuess(buffer, answer);
    strcpy(guessArray[*turn], buffer);
    //increment turn
    *turn = *turn + 1;
    printBoard(guessArray, *turn);
    printf("turn over\n");
    //detach shared memory
    shmdt(turn);
    shmdt(answer);
    shmdt(guessArray);
    // release and increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
  }
}
/*
int main(){
    printf("You ran out of tries! The word was \"%s\".", answer);
}
*/