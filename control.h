#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef CONTROL_H
#define CONTROL_H
/*
Creates word and file to store guesses
*/
void gameSetup();
/*
Takes a 5-letter string, prints color-coded result
*/
void checkGuess(char* word);
#endif
