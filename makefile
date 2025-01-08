run: play
	@./play

compile play: play.o game.o
	@gcc -o play play.o game.o

play.o: play.c game.h
	@gcc -c play.c

game.o: game.c game.h
	@gcc -c game.c

clean:
	@rm play *.o