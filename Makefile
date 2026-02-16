 # @brief Makefile for the Castle game
 #
 # @file Makefile
 # @author Santiago Pita and Mario Rodriguez
 # @version 1
 # @date 07-02-2025

 #EXE is the name the .exe will have
 #OBJS references .o files
 #CFLAGS flags used for warnings and style
 #CC stands for compilation command

EXE = castle
OBJS= game.o command.o game_loop.o game_reader.o graphic_engine.o object.o player.o space.o game_actions.o
CFLAGS = -Wall -ansi -pedantic -g
CC = gcc
CLIB = -lscreen -L.

all: $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $@ $^ $(CLIB)

game.o: game.c game.h object.h player.h game_reader.h command.h space.h types.h
	$(CC) -c $(CFLAGS) game.c

command.o : command.c command.h types.h
	$(CC) -c $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h player.h
	$(CC) -c $(CFLAGS) $<

game_loop.o: game_loop.c command.h game.h game_actions.h graphic_engine.h types.h space.h
	$(CC) -c $(CFLAGS) $<

game_reader.o: game_reader.c game.h command.h types.h space.h
	$(CC) -c $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h space.h types.h libscreen.h
	$(CC) -c $(CFLAGS) $<

object.o: object.c object.h types.h
	$(CC) -c $(CFLAGS) $<
	
player.o: player.c player.h types.h
	$(CC) -c $(CFLAGS) $<

space.o: space.c space.h types.h
	$(CC) -c $(CFLAGS) $<

 #cleans the .o and .exe files (used before uploading to git)
clean: 
	rm -f *.o $(EXE)

 #runs Iteration 1 map
run:
	./$(EXE) castle.dat

 #runs Iteration 2 map
runmap:
	./$(EXE) nuevomapa.dat