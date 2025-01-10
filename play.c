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
    char* answer = "arise";
    char buffer[BUFFERSIZE];
    printBoard(guessArray, turn);
    for (int i = 0; i < 6; i++){
        printf("Enter a 5-letter word\n");
        fgets(buffer, BUFFERSIZE, stdin);
        printf("1");
        checkGuess(buffer, answer);
        guessArray[0] = buffer;
        turn++;
        printBoard(guessArray, turn);
    }
}