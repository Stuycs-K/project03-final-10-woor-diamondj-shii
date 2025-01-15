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
#define ANSWERSHMKEY 98195187

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main() {
  //initialize global variables
  char* answer = (char*) malloc(6 * sizeof(char));
  int gameStatus = 0;
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
    //access char* answer
    int shmid = shmget(ANSWERSHMKEY, 0, 0);
    answer = shmat(shmid, 0, 0);
    //access guess file
    int guessFile = open("guesses.txt", O_RDWR | O_APPEND);
    // making turn
    gameStatus = printBoard(answer);
    //print any game-end messages
    if (gameStatus == 1){
      printf("The other player guessed the word!\n");
      exit(0);
    }
    if (gameStatus == 2){
      printf("You ran out of turns! The word was \"%s\"\n", answer);
      exit(0);
    }
    char buffer[BUFFERSIZE] = {'\0'};
    printf("Enter a 5-letter word.\n");
    fgets(buffer, BUFFERSIZE, stdin);
    *(strchr(buffer, '\n')) = '\0';
    while (isValidGuess(buffer) == 0){
      printf("Invalid guess. Please enter a 5-letter word.\n");
      fgets(buffer, BUFFERSIZE, stdin);
      *(strchr(buffer, '\n')) = '\0';
    }
    //check if answer is guessed
    if (strcmp(buffer, answer) == 0){
      gameStatus = 1;
    }
    checkGuess(buffer, answer);
    *(strchr(buffer, '\0')) = '\n';
    write(guessFile, buffer, strlen(buffer));
    printBoard(answer);
    //detach shared memory
    shmdt(answer);
    // release and increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
    //print message if answer was guessed
    if (gameStatus == 1){
      printf("You guessed the word!\n");
      exit(0);
    }
  }
}