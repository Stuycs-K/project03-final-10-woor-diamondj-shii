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

#define BUFFERSIZE 200
//colors
#define GRAY "\033[100m"
#define YELLOW "\033[43m"
#define GREEN "\033[102m"
#define RESET "\033[49m"

void printBoard(char* guessArray[], int turn){
    for (int i = 0; i < 6; i++){
        if (turn > i){
            printf("%s", guessArray[i]);
        }
        else{
            printf("_____\n");
        }
    }
}

char* checkGuess(char* guess, char* answer){
    char formattedGuess[BUFFERSIZE];
    //format each letter
    for (int i = 0; i < strlen(guess); i++){
        char letter = guess[i];
        char* formattedLetter;
        //make green if letter is in correct spot
        if (letter == answer[i]){
            sprintf(formattedLetter, "%s%c%s", GREEN, letter, RESET);
        }
        else{
            //make yellow if letter is in present but in the wrong spot
            if (strchr(answer, letter) != NULL){
                sprintf(formattedLetter, "%s%c%s", YELLOW, letter, RESET);
            }
            else{
                //make gray if letter isn't present
                if (strchr(answer, letter) != NULL){
                    sprintf(formattedLetter, "%s%c%s", GRAY, letter, RESET);
                }
            }
        }
        strcat(formattedGuess, formattedLetter);
    }
    strcat(formattedGuess, "\n");
    return formattedGuess;
}