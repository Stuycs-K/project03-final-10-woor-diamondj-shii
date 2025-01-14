.PHONY: client server clean compile

client: client_exe
	@./client_exe
server: server_exe
	@./server_exe
compile: client_exe server_exe
client_exe: client.o pipe_networking.o game.o
	@gcc -o client_exe client.o pipe_networking.o game.o
server_exe: server.o pipe_networking.o control.o
	@gcc -o server_exe server.o pipe_networking.o control.o
client.o: client.c pipe_networking.h game.h
	@gcc -c client.c
server.o: server.c pipe_networking.h
	@gcc -c server.c
pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c
game.o: game.c game.h
	@gcc -c game.c
control.o: control.c control.h
	@gcc -c control.c
clean:
	@rm -f *.o client_exe server_exe guesses.txt *.gch
