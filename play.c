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