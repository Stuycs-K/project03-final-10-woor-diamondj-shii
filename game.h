#ifndef GAME_H
#define GAME_H
/*
Prints the game board with all previous results and underscores for remaining guesses, or a blank screen if it's the first turn
*/
void printBoard();
/*
Takes a 5-letter string, prints color-coded result
*/
void checkGuess(char* guess, char* answer);
#endif