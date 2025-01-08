#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#ifndef GAME_H
#define GAME_H
/*
Prints the game board with all previous results and underscores for remaining guesses, or a blank screen if it's the first turn
*/
void printBoard();
/*
Takes a 5-letter string, prints color-coded result
*/
void checkGuess(char* word);
#endif
