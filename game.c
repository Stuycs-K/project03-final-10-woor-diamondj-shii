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

int printBoard(char* answer){
    //gameStatus: 0 - continue game, 1 - word was guessed correctly, 2 - ran out of turns
    int gameStatus = 0;
    FILE * guessFile = fopen("guesses.txt", "r");
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