# Final Project Proposal

## Group Members:

Julien Diamond, Ronnie Woo, Ian Shi
       
# Intentions:

We will be creating a collaborative adaptation of Wordle. A five letter word is selected at random, and two players will take turns making a guess. Each player will have information regarding their own guesses and that of the other player.
    
# Intended usage:

During each turn, players will be shown all previous guesses. The characters will be colored to show if they are in the right spot, or if the character is in the word but in the wrong spot (same color scheme as the actual wordle)

Players will then be prompted to enter a six letter word.

After all six guesses are used or a player guesses the right word, the game will end, and both players will be shown the results.
  
# Technical Details:

The word will be selected at random from a file of predetermined words. We will be using semaphores to ensure a player does not make a turn while the other player is making a turn. Guesses will be stored as strings, which involves memory allocation. We will use signal interception to alert a player if the other player quits the game with ctrl + c. Upon the conclusion of the game, the result will be stored in a file. 

Division of labor:
- Julien: Semaphore system to create turns, game conclusion wPleasehen correct word - guessed
- Ian: Signal handling to indicate player quitting, Color-coded information about guesses
- Ronnie: Files to choose word and store result, previous guesses displayed

Notable algorithms:
- generate random word
- display color-coded previous guesses
- display game conclusion information
- store results in file
    
# Intended pacing:

- Jan 6 (Mon): Begin project
- Jan 10 (Fri): Players can take turns with semaphores, and at the start of each turn, the game will display all previous guesses
- Jan 13 (Mon): A word is selected at random from a file, the game will terminate when the correct word was guessed, and color-coded information about previous guesses is displayed
- Jan 17 (Fri): Results stored in a file, and signal handling is used to display when one player quits
- Jan 20 (Mon): Video demo 
- Jan 21 (Tue): Project due
