# Dev Log:

This document must be updated daily by EACH group member.

## Ronnie Woo

### 2024-01-06 (class period)
Finished and uploaded proposal, began skeleton files
found text files with valid wordle words that we could potentially use later

answers only: https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b

allowed guesses besides answers: https://gist.github.com/cfreshman/cdcdf777450c5b5301e439061d29694c 

valid answers and guesses: https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93

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

### 2025-1-10 (class period)
accept two clients and send shmkey and semkey to them. worked with julien for this.

### 2025-1-09 (at home)
Started server stuff

### 2025-01-08 (class period)

Added a txt file to represent all possible answers, and made a function to generate a word from that list.

### 2025-01-06 (class period)
Finished and uploaded proposal, began skeleton files
