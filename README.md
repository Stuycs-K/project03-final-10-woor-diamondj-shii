[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# Wordles with Friends

### JulIan Woo [38]

Julien Diamond, Ronnie Woo, Ian Shi

### Project Description:

This is a collaborative version of Wordle. A five letter word is selected at random, and two players will take turns making a guess. Each player will have information regarding their own guesses and that of the other player. The game is handled by a server that forks a subserver for every pair of two clients to start a game, and it can run multiple games at once.

### Instructions:

One terminal runs `make server` to setup the server. Two other terminals then connect by running `make client` to connect to the server. Once two players have joined, they will be shuttled into a game. Players will be prompted to enter a word when it is their turn and the game will end automatically when one of the game end conditions is met.

### BUGS beatles and other insects:

- breaks if first client quits before second client connects
