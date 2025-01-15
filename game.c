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

void printBoard(int gameID) {
  char* gameName = (char*) malloc(20 * sizeof(char));
  sprintf(gameName, "guesses%d.txt", gameID);
  FILE* guessFile = fopen(gameName, "r");
  for (int i = 0; i < 6; i++) {
    char guess[BUFFERSIZE];
    // print all previous guesses
    if (fgets(guess, BUFFERSIZE, guessFile) != NULL) {
      printf("%s\n", guess);
    }
    // print empty lines for remaining guesses
    else {
      printf("_____\n");
    }
  }
}

void checkGuess(char* guess, char* answer){
    char formattedGuess[BUFFERSIZE] = {'\0'};
    //format each letter
    for (int i = 0; i < strlen(guess); i++){
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

int isValidGuess(char* guess) {
  // return false if length isn't 5
  if (strlen(guess) != 5) {
    return 0;
  }
  for (int i = 0; i < 5; i++) {
    //return false if any character isn't a letter
    if (!(guess[i] >= 'a' && guess[i] <= 'z' || guess[i] >= 'A' && guess[i] <= 'Z')) {
      return 0;
    }
    // change all uppercase letters to lowercase
    if (guess[i] >= 'A' && guess[i] <= 'Z') {
      guess[i] = guess[i] + 'a' - 'A';
    }
  }
  return 1;
}

void runGame(int semkey, int shmkey, int gameID) {
  //initialize global variables
  char* answer = (char*) malloc(6 * sizeof(char));
  int win = 0;
  while (1) {
    // access semaphore
    printf("waiting for turn...\n");
    int semd = semget(semkey, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;

    // decrement semaphore
    semop(semd, &sb, 1);
    printf("semaphore accessed\n");

    //access char* answer
    int shmid = shmget(shmkey, 0, 0);
    answer = shmat(shmid, 0, 0);

    //access guess file
    char* gameName = (char*) malloc(20 * sizeof(char));
    sprintf(gameName, "guesses%d.txt", gameID);
    printf("gameName = %s\n", gameName);
    int guessFile = open(gameName, O_RDWR | O_APPEND);

    // making turn
    printBoard(gameID);
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
    printBoard(gameID);

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
