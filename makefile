compile: control.o game.o
	gcc -o ctrl control.o
	gcc -o game game.o
control.o: control.c control.h
	gcc -c control.c
control:
	./ctrl $(ARGS)
game.o: game.c game.h
	gcc -c game.c
clean:
	rm -f ctrl game *.o guesses.txt
