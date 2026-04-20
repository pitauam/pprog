 # @brief Makefile for the Castle game
 #
 # @file Makefile
 # @author Santiago Pita and Mario Rodriguez
 # @version 6
 # @date 11-04-2026

#EXE is the name the .exe will have
EXE = castle
#OBJS references .o files
OBJS = obj/game.o obj/space.o obj/command.o obj/game_loop.o obj/game_reader.o obj/graphic_engine.o obj/object.o obj/player.o obj/game_actions.o obj/set.o obj/character.o obj/inventory.o obj/link.o
#CFLAGS flags used for warnings and style
CFLAGS = -Wall -ansi -pedantic -g -I./include
#CC stands for compilation command
CC = gcc
#CLIB are the libraries used when compiling
CLIB = -lscreen -L./lib
#TESTS is used when cleaning
TESTS = spacetest settest charactertest linktest inventorytest

#by default it makes the castle game executable
all: $(EXE)

#runs auxiliary map
runaux:
	./$(EXE) dat/anthill.dat

#runs all tests
runtests: 
	./spacetest && ./settest && ./charactertest && ./linktest && ./inventorytest

#makes all tests
alltests:
	make spacetest && make settest && make charactertest && make linktest && make inventorytest

#makes main game exe file
$(EXE) : $(OBJS)
	$(CC) -o $@ $^ $(CLIB)

#makes all .o game files
obj/game.o: src/game.c include/game.h include/command.h include/types.h include/space.h include/set.h include/object.h include/player.h include/character.h include/link.h
	$(CC) -c $(CFLAGS) src/game.c -o $@

obj/command.o : src/command.c include/command.h include/types.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/game_actions.o: src/game_actions.c include/game_actions.h include/command.h include/types.h include/game.h include/space.h include/object.h include/player.h include/set.h include/link.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/game_loop.o: src/game_loop.c include/command.h include/game.h include/game_actions.h include/graphic_engine.h include/types.h include/space.h include/set.h include/game_reader.h
	$(CC) -c $(CFLAGS) $< -o $@
	
obj/game_reader.o: src/game_reader.c include/game.h include/command.h include/types.h include/space.h include/set.h include/link.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/graphic_engine.o: src/graphic_engine.c include/graphic_engine.h include/game.h include/command.h include/space.h include/types.h include/libscreen.h include/set.h include/link.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/object.o: src/object.c include/object.h include/types.h
	$(CC) -c $(CFLAGS) $< -o $@
    
obj/player.o: src/player.c include/player.h include/types.h include/link.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/space.o: src/space.c include/space.h include/types.h include/set.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/set.o: src/set.c include/set.h include/types.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/character.o: src/character.c include/character.h include/types.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/link.o: src/link.c include/link.h include/types.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/inventory.o: src/inventory.c include/inventory.h include/types.h include/set.h
	$(CC) -c $(CFLAGS) $< -o $@
    
#runs Iteration 3 map and generates a log file
run: $(EXE)
	./$(EXE) dat/castle.dat

#run
runlog: $(EXE)
	./$(EXE) dat/castle.dat -l logFile
#runs Iteration 3 map with valgrind and generates a log file
runv: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) dat/castle.dat -l logFile

#runs anthill map with valgrind
runvanthill:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) dat/anthill.dat

#makes tests .exe
spacetest: obj/space_test.o obj/space.o obj/set.o
	$(CC) -o $@ $^
    
settest: obj/set_test.o obj/set.o
	$(CC) -o $@ $^

charactertest: obj/character_test.o obj/character.o
	$(CC) -o $@ $^

linktest: obj/link_test.o obj/link.o
	$(CC) -o $@ $^

inventorytest: obj/inventory_test.o obj/inventory.o obj/set.o
	$(CC) -o $@ $^

#makes tests .o
obj/space_test.o: src/space_test.c include/space.h include/types.h include/set.h include/space_test.h include/test.h
	$(CC) -c $(CFLAGS) $< -o $@
    
obj/set_test.o: src/set_test.c include/set.h include/types.h include/test.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/character_test.o: src/character_test.c include/character.h include/types.h include/test.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/link_test.o: src/link_test.c include/link.h include/types.h include/link_test.h include/test.h
	$(CC) -c $(CFLAGS) $< -o $@

obj/inventory_test.o: src/inventory_test.c include/inventory.h include/types.h include/set.h include/inventory_test.h include/test.h
	$(CC) -c $(CFLAGS) $< -o $@

#runs each test
runspacetest: 
	./spacetest

runsettest: settest
	./settest

runcharactertest: charactertest
	./charactertest

runlinktest: linktest
	./linktest

runinventorytest: inventorytest
	./inventorytest

#documentation with Doxygen
#.phony is used to let makefile know the following instruction is a command
.PHONY: doc
doc:
	doxygen Doxyfile
	@echo "Doxygen documentation created. open the .html file in html/"

 #cleans the .o and .exe files (used before uploading to git)
clean: 
	rm -f obj/*.o rem -f *.o $(EXE) $(TESTS) log.txt