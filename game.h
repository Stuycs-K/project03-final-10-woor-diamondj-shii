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
Prints the game board with all previous results and underscores for remaining guesses, or a blank screen if it's the first turn, takes an array of all entered guesses and the current turn number
*/
void printBoard(char* guessArray[], int turn);
/*
Takes a 5-letter string as a guess, returns color-coded result
*/
void checkGuess(char* guess, char* answer);
#endif
