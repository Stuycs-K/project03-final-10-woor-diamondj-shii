# Dev Log:

This document must be updated daily by EACH group member.

## Ronnie Woo

### 2025-01-06
Finished and uploaded proposal, began skeleton files (class period)
found text files with valid wordle words that we could potentially use later (20 min)

answers only: https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b

allowed guesses besides answers: https://gist.github.com/cfreshman/cdcdf777450c5b5301e439061d29694c 

valid answers and guesses: https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93

### 2025-01-07
created my own branch
made blank printBoard() and checkGuess() with correct logic (class period)
mostly finished looping for multiple guesses from the user (40 min)

### 2025-01-08
created new play.c file and changed how checkGuess and printBoard take parameters (class period)
still getting segfault with strings somewhere, trying to fix (30 min)

### 2025-01-09
fixed segfaults in checkGuess() and printBoard(), made main game loop work with proper logic for all 6 turns in singleplayer, updated header comments (class period + 45 min)

### 2025-01-10
merged singleplayer base game to main, began combining base game with semaphore and shared memory features (class period)

### 2025-01-11 & 2025-01-12
added global game variable initialization in gameSetup() in control.c, still combining mains in play.c (35 min)

### 2025-01-13
got both clients to access shared memory, need to fix shared guessArray (class period)
changed from storing guesses in an array to writing them to a file, both clients can properly write to the file and print contents (40 min)

### 2025-01-14
removed shared int for turn, started making game end logic (class period)
removed game end logic (can be done in subserver), added checking for valid guesses (length of 5 and only letters) (35 min)

### 2025-01-15
game ends after 6 turns, adding game ends when correct answer is guessed (class period)
game ends when correct answer is guessed (40 min)

### 2025-01-16
merged features together and tested (class period)

## Julien Diamond

### 2025-01-06 (class period)
Finished and uploaded proposal, began skeleton files

### 2025-01-07 (class period)
Wrote makefile, setup() function to create semaphores and guess file, started function to remove semaphore

### 2025-01-07 (20 mins)
Fixed remove semaphore function + added remove file feature, control.c now controllable via args `setup` and `reset`

### 2025-01-08 (class period)
Starting implementing answer string stored in shared memory

### 2025-01-09 (class period)
Brainstormed restructuring of project for added complexity, will now aim for forking server that sends every two consecutive clients into a game

### 2025-01-10 (30 minutes)
`control.c` now creates and removes a string in shared memory, which is accessable by clients; the randomly generated answer is now stored in that shared memory upon called `make control ARGS="setup"`

### 2025-01-10 (class period)
pair programmed to begin working on server/subserver and client implementation

### 2025-01-13 (20 minutes)
fixed some server-related errors

### 2025-01-13 (class period)
pair programmed to continue working on server implementation including select to read from both client at once

### 2025-01-14 (35 minutes)
fixed errors associated with sending semkey/shmkey/pid to clients, worked on string in shm segfault

### 2025-01-14 (class period)
pair programmed to continue working on server setup---successful forking to match two clients to a game; began working on linking wordle with server/client system

### 2025-01-15 (35 minutes)
merged wordle into server/client system; bug in word display (only shows 4 letters)

### 2025-01-15 (class period)
pair programmed to allow multiple games to run simultaneously by giving each a gameID

### 2025-01-16 (20 minutes)
wrote code to handle client1 quitting before game, but need to detect quit and decrement numClients for it to be put into action

## Ian Shi

### 2025-1-14 (at home)
delete shm and sem key after ending game, get rid of debugging print statements for the server client handshake

### 2025-1-14 (class period)
fix segfault error when accessing shared memory for answer

### 2025-1-13 (class period)
start working on interaction between server and client for exiting. worked with julien for this.

### 2025-1-10 (class period)
accept two clients and send shmkey and semkey to them. worked with julien for this.

### 2025-1-09 (at home)
Started server stuff

### 2025-01-08 (class period)

Added a txt file to represent all possible answers, and made a function to generate a word from that list.

### 2025-01-06 (class period)
Finished and uploaded proposal, began skeleton files
