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

void runGame(int semkey, int shmkey, int gameID) {
  char* answer = (char*) malloc(6 * sizeof(char));
  int gameStatus = 0;
  while (1) {
    // wait to access semaphore
    printf("waiting for turn...\n");
    int semd = semget(semkey, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    // decrement semaphore once accessed
    semop(semd, &sb, 1);
    //access char* answer
    int shmid = shmget(shmkey, 0, 0);
    answer = (char*) shmat(shmid, 0, 0);
    //access guess file
    char* gameName = (char*) malloc(20 * sizeof(char));
    sprintf(gameName, "guesses%d.txt", gameID);
    int guessFile = open(gameName, O_RDWR | O_APPEND);
    // making turn
    gameStatus = printBoard(answer, gameID);
    //print any game-end messages
    if (gameStatus == 1){
      printf("The other player guessed the word!\n");
      return;
    }
    if (gameStatus == 2){
      printf("You ran out of turns! The word was \"%s\"\n", answer);
      return;
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
    printBoard(answer, gameID);
    //detach shared memory
    shmdt(answer);
    // release and increment semaphore
    sb.sem_op = 1;
    semop(semd, &sb, 1);
    //print message if answer was guessed
    if (gameStatus == 1){
      printf("You guessed the word!\n");
      return;
    }
  }
}

int printBoard(char* answer, int gameID){
    //gameStatus: 0 - continue game, 1 - word was guessed correctly, 2 - ran out of turns
    int gameStatus = 0;
    char* gameName = (char*) malloc(20 * sizeof(char));
    sprintf(gameName, "guesses%d.txt", gameID);
    FILE* guessFile = fopen(gameName, "r");
    for (int i = 0; i < 6; i++){
        char guess[BUFFERSIZE];
        //print all previous guesses
        if (fgets(guess, BUFFERSIZE, guessFile) != NULL){
            printf("%s", guess);
            //return 1 if word was guessed correctly
            if (guess[6] == answer[0] && guess[18] == answer[1] && guess[30] == answer[2] && guess[42] == answer[3] && guess[54] == answer[4]){
                gameStatus = 1;
            }
            //return 2 if no more turns;
            else{
                if (i == 5){
                    gameStatus = 2;
                }
            }
        }
        //print empty lines for remaining guesses
        else{
            printf("_____\n");
        }
    }
    return gameStatus;
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

int isValidGuess(char* guess){
    //return false if length isn't 5
    if (strlen(guess) != 5){
        return 0;
    }
    for (int i = 0; i < 5; i++){
        //return false if any character isn't a letter
        if (!(guess[i] >= 'a' && guess[i] <= 'z' || guess[i] >= 'A' && guess[i] <= 'Z')){
            return 0;
        }
        //change all uppercase letters to lowercase
        if (guess[i] >= 'A' && guess[i] <= 'Z'){
            guess[i] = guess[i] + 'a' - 'A';
        }
    }
    return 1;
}
