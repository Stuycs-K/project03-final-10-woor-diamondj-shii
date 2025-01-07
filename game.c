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

void printBoard(){
    for (int i = 0; i < 5; i++){
        printf("_____\n");
    }
}

void checkGuess(char* word){

}

int main(){
    printBoard();
}