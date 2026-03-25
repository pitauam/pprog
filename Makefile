 # @brief Makefile for the Castle game
 #
 # @file Makefile
 # @author Santiago Pita and Mario Rodriguez
 # @version 5
 # @date 17-03-2025

#EXE is the name the .exe will have
EXE = castle
#OBJS references .o files
OBJS = game.o space.o command.o game_loop.o game_reader.o graphic_engine.o object.o player.o game_actions.o set.o character.o inventory.o link.o
#CFLAGS flags used for warnings and style
CFLAGS = -Wall -ansi -pedantic -g
#CC stands for compilation command
CC = gcc
#CLIB are the libraries used when compiling
CLIB = -lscreen -L.
#TESTS is used when cleaning
TESTS = spacetest settest charactertest

#by default it makes the castle game executable
all: $(EXE)

#runs auxiliary map
runaux:
	./$(EXE) anthill.dat

#runs all tests
runtests: 
	./spacetest && ./settest && ./charactertest

#makes all tests
alltests:
	make spacetest && make settest && make charactertest

#makes main game exe file
$(EXE) : $(OBJS)
	$(CC) -o $@ $^ $(CLIB)

#makes all .o game files
game.o: game.c game.h command.h types.h space.h set.h object.h player.h character.h link.h
	$(CC) -c $(CFLAGS) game.c

command.o : command.c command.h types.h
	$(CC) -c $(CFLAGS) $<

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h object.h player.h set.h link.h
	$(CC) -c $(CFLAGS) $<

game_loop.o: game_loop.c command.h game.h game_actions.h graphic_engine.h types.h space.h set.h
	$(CC) -c $(CFLAGS) $<

game_reader.o: game_reader.c game.h command.h types.h space.h set.h link.h
	$(CC) -c $(CFLAGS) $<

graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h space.h types.h libscreen.h set.h link.h
	$(CC) -c $(CFLAGS) $<

object.o: object.c object.h types.h
	$(CC) -c $(CFLAGS) $<
	
player.o: player.c player.h types.h link.h
	$(CC) -c $(CFLAGS) $<

space.o: space.c space.h types.h set.h
	$(CC) -c $(CFLAGS) $<

set.o: set.c set.h types.h
	$(CC) -c $(CFLAGS) $<

character.o: character.c character.h types.h
	$(CC) -c $(CFLAGS) $<

link.o: link.c link.h types.h
	$(CC) -c $(CFLAGS) $<

inventory.o: inventory.c inventory.h types.h set.h
	$(CC) -c $(CFLAGS) $<

	
#runs Iteration 3 map
run:
	./$(EXE) castle.dat

#runs Iteration 3 map with valgrind
runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) castle.dat

#runs anthill map with valgrind
runvanthill:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) anthill.dat

#makes tests .exe
spacetest: space_test.o space.o set.o
	$(CC) -o $@ $^
	
settest: set_test.o set.o
	$(CC) -o $@ $^

charactertest: character_test.o character.o
	$(CC) -o $@ $^

#makes tests .o
space_test.o: space_test.c space.h types.h set.h space_test.h test.h
	$(CC) -c $<
	
set_test.o: set_test.c set.h types.h test.h
	$(CC) -c $(CFLAGS) $<

character_test.o: character_test.c character.h types.h test.h
	$(CC) -c $(CFLAGS) $<

#runs each test
runspacetest: 
	./spacetest

runsettest: settest
	./settest

runcharactertest: charactertest
	./charactertest

 #cleans the .o and .exe files (used before uploading to git)
clean: 
	rm -f *.o $(EXE) $(TESTS)