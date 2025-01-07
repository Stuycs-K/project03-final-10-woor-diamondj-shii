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

//colors
#define GRAY "\033[100m"
#define YELLOW "\033[43m"
#define GREEN "\033[102m"
#define RESET "\033[49m"

void printBoard(){
    for (int i = 0; i < 5; i++){
        printf("_____\n");
    }
}

void checkGuess(char* guess, char* answer){
    //print each letter
    for (int i = 0; i < strlen(guess); i++){
        char letter = guess[i];
        //print green if letter is in correct spot
        if (letter == answer[i]){
            printf("%s%c%s", GREEN, letter, RESET);
        }
        else{
            //print yellow if letter is in present but in the wrong spot
            if (strchr(answer, letter) != NULL){
                printf("%s%c%s", YELLOW, letter, RESET);
            }
            else{
                //print gray if letter isn't present
                if (strchr(answer, letter) != NULL){
                    printf("%s%c%s", GRAY, letter, RESET);
                }
            }
        }
    }
    printf("\n");
}

int main(){
    printBoard();
    char* answer = "arise";
    checkGuess("raise", answer);
}