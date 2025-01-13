run: play
	@./play

control: ctrl
	@./ctrl $(ARGS)

server: server.o pipe_networking.o
	@gcc -o server server.o pipe_networking.o
	@./server

run_client: client.o pipe_networking.o
	@gcc -o client client.o pipe_networking.o
	@./client

compile play ctrl: play.o control.o game.o
	@gcc -o play play.o game.o
	@gcc -o ctrl control.o

play.o: play.c game.h
	@gcc -c play.c

control.o: control.c control.h
	@gcc -c control.c

game.o: game.c game.h
	@gcc -c game.c

server.o: server.c pipe_networking.h
	@gcc -c server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

clean:
	@rm -f play ctrl client server *.o guess.txt
