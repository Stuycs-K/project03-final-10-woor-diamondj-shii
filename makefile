run: play
	@./play

control: ctrl
	@./ctrl $(ARGS)

compile play ctrl: play.o control.o game.o
	@gcc -o play play.o game.o
	@gcc -o ctrl control.o

play.o: play.c game.h
	@gcc -c play.c

control.o: control.c control.h
	@gcc -c control.c

game.o: game.c game.h
	@gcc -c game.c

clean:
	@rm play ctrl *.o guess.txt