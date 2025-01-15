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

## Julien Diamond

### 2024-01-06 (class period)
Finished and uploaded proposal, began skeleton files

### 2024-01-07 (class period)
Wrote makefile, setup() function to create semaphores and guess file, started function to remove semaphore

### 2024-01-07 (20 mins)
Fixed remove semaphore function + added remove file feature, control.c now controllable via args `setup` and `reset`

### 2024-01-08 (class period)
Starting implementing answer string stored in shared memory

### 2024-01-09 (class period)
Brainstormed restructuring of project for added complexity, will now aim for forking server that sends every two consecutive clients into a game

### 2024-01-10 (30 minutes)
`control.c` now creates and removes a string in shared memory, which is accessable by clients; the randomly generated answer is now stored in that shared memory upon called `make control ARGS="setup"`

## Ian Shi

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
