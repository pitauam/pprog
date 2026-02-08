#Castle game Makefile
#EXE es el nombre del .exe
#OBJS son los .o
#CFLAGS son las banderas para warnings y estilo
#CC es el comando de compilacion

EXE = castle
OBJS= game.o command.o game_loop.o game_reader.o graphic_engine.o object.o player.o space.o game_actions.o
CFLAGS = -Wall -pedantic -ansi -g
CC = gcc

all: $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^ -lscreen -L.

game.o: game.c game.h object.h player.h game_reader.h command.h space.h types.h
	$(CC) -c $(CFLAGS) game.c

command.o : command.c command.h types.h
	$(CC) -c $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h game.h space.h types.h
	$(CC) -c $(CFLAGS) $<

game_loop.o: game_loop.c command.h game.h game_actions.h graphic_engine.h types.h space.h
	$(CC) -c $(CFLAGS) $<

game_reader.o: game_reader.c game.h command.h types.h space.h
	$(CC) -c $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h space.h types.h libscreen.h
	$(CC) -c $(CFLAGS) $<

object.o: object.c object.h game.h
	$(CC) -c $(CFLAGS) $<
	
player.o: player.c player.h game.h
	$(CC) -c $(CFLAGS) $<

space.o: space.c space.h
	$(CC) -c $(CFLAGS) $<



clean: 
	rm -f *.o $(EXE)

