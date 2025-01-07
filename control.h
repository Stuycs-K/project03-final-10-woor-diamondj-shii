#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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
/*
removes guesses.txt and removes semaphore
*/
void reset();
#endif
