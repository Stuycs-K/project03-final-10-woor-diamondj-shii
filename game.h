#ifndef GAME_H
#define GAME_H
/*
Prints the game board with all previous results and underscores for remaining guesses, or a blank screen if it's the first turn
*/
void printBoard(char* guessArray[], int turn);
/*
Takes a 5-letter string, prints color-coded result
*/
char* checkGuess(char* guess, char* answer);
#endif