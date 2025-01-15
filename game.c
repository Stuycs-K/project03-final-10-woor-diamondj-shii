#include <dirent.h>
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
//colors
#define GRAY "\033[100m"
#define YELLOW "\033[43m"
#define GREEN "\033[102m"
#define RESET "\033[49m"

int err() {
  printf("errno %d\n", errno);
  printf("%s\n", strerror(errno));
  exit(1);
}

void printBoard(char* guessArray[], int turn){
    for (int i = 0; i < 6; i++){
        //print all previous guesses
        if (turn > i){
            printf("%s\n", guessArray[i]);
        }
        //print empty lines for remaining guesses
        else{
            printf("_____\n");
        }
    }
}

void checkGuess(char* guess, char* answer){
    char formattedGuess[BUFFERSIZE] = {'\0'};
    //format each letter
    for (int i = 0; i < strlen(guess) - 1; i++){
        char letter = guess[i];
        char formattedLetter[BUFFERSIZE] = {'\0'};
        //make background green if letter is in correct spot
        if (letter == answer[i]){
            sprintf(formattedLetter, "%s%c%s", GREEN, letter, RESET);
        }
        else{
            //make background yellow if letter is present but in the wrong spot
            if (strchr(answer, letter) != NULL){
                sprintf(formattedLetter, "%s%c%s", YELLOW, letter, RESET);
            }
            else{
                //make background gray if letter isn't present
                sprintf(formattedLetter, "%s%c%s", GRAY, letter, RESET);
            }
        }
        strcat(formattedGuess, formattedLetter);
    }
    strcpy(guess, formattedGuess);
}

void runGame(int semkey, int shmkey) {
  //initialize global variables
  char* answer = (char*) malloc(6 * sizeof(char));
  int win = 0;
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
    printBoard();
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
      win = 1;
    }
    checkGuess(buffer, answer);
    *(strchr(buffer, '\0')) = '\n';
    write(guessFile, buffer, strlen(buffer));
    printBoard();

    //print message if answer is guessed
    if (win == 1){
      printf("You guessed the word!\n");
    }

    //detach shared memory
    shmdt(answer);
    
    // release and increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
  }
}
