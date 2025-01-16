[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Vh67aNdh)
# Wordles with Friends

### JulIan Woo [38]

Julien Diamond, Ronnie Woo, Ian Shi

### Project Description:

This is a collaborative adaptation of Wordle. A five letter word is selected at random, and two players will take turns making a guess. Each player will have information regarding their own guesses and that of the other player.

### Instructions:

The user uses `make compile` to compile the program. The game is set up with `./control`, and players take turns by running `./game`.

After running `./game`, information about past guesses will be displayed, and the user will be prompted to enter the next guess. To take their next turn, the user runs `./game` again.

### BUGS beatles and other insects:

- breaks if first client quits before second client connects
