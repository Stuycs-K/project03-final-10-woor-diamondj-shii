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