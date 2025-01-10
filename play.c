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
#define SHMKEY 98195187

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main() {
  while (1) {
    // access semaphore
    printf("waiting for turn...\n");
    int semd = semget(SEMKEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;

    // decrement semaphore
    semop(semd, &sb, 1);

    // accessing shared data
    char* answer = (char*) malloc(6 * sizeof(char));
    int shmid = shmget(SHMKEY, 0, 0);
    answer = shmat(shmid, 0, 0);

    // simulating turn
    printf("answer is %s\n", answer);
    printf("taking turn (3 seconds)\n");
    sleep(3);
    printf("turn over\n");

    // increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
  }
}

int main(){
    int turn = 0;
    char* guessArray[6];
    for (int i = 0; i < 6; i++){
        guessArray[i] = malloc(BUFFERSIZE);
    }
    char* answer = "arise";
    printBoard(guessArray, turn);
    for (int i = 0; i < 6; i++){
        char buffer[BUFFERSIZE] = {'\0'};
        printf("Enter a 5-letter word\n");
        fgets(buffer, BUFFERSIZE, stdin);
        checkGuess(buffer, answer);
        strcpy(guessArray[i], buffer);
        turn++;
        printBoard(guessArray, turn);
    }
    printf("You ran out of tries! The word was \"%s\".", answer);
}