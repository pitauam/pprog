#Castle game Makefile
#Binary es el nombre del .exe
#Objs son los .o
#Cflags son las banderas para warnings y estilo
#CC es el comando de compilacion

EXE = castillo
OBJS= game.o command.o game_loop.o game_reader.o  graphic_engine.o object.o player.o space.o
CFLAGS = -Wall -pedantic -ansi -g
CC = gcc

all: $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^

game.o: game.c game.h object.h player.h game_reader.h command.h space.h types.h
	$(CC) -c $(CFLAGS) game.c

command.o : command.c command.h types.h
	$(CC) -c $(CFLAGS) $<

game_loop.o: game_loop.o command.h game.h game_actions.h graphic_engine.h types.h space.h
	$(CC) -c $(CFLAGS) $<

game_reader.o: game_reader.c game.h command.h types.h space.h
	$(CC) -c $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h space.h types.h libscreen.h
	$(CC) -c $(CFLAGS) $<

object.o: object.c object.h types.h
	$(CC) -c $(CFLAGS) $<
	
player.o: player.c player.h types.h
	$(CC) -c $(CFLAGS) $<

space.o: space.c space.c space.h
	$(CC) -c $(CFLAGS) $<




clean: 
	rm -f *.o $(EXE)

