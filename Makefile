#===================================HEADERS===================================#
MAKE=gcc -g -Wall -pedantic -ansi -I./lib/ 
OBJ= ./obj/command.o ./obj/die.o ./obj/game.o ./obj/game_loop.o ./obj/game_management.o ./obj/graphic_engine.o ./obj/inventory.o ./obj/link.o ./obj/object.o ./obj/player.o ./obj/screen.o ./obj/set.o ./obj/space.o ./obj/menu.o ./obj/dialogue.o
OBJGAME= ./obj/command.o ./obj/die.o ./obj/game.o ./obj/game_management.o ./obj/graphic_engine.o ./obj/inventory.o ./obj/link.o ./obj/object.o ./obj/player.o ./obj/screen.o ./obj/set.o ./obj/space.o ./obj/menu.o ./obj/dialogue.o
NFD=-m64 -no-pie -s -lnfd `pkg-config --libs gtk+-3.0` -L/usr/lib64 -L./lib/ ./lib/libnfd.a

#=====================================ALL=====================================#
all: SuperGoose_64 run
full: doxygen dist doxylink test_create SuperGoose_64 test valgrind

#================================MAIN PROGRAMS================================#
SuperGoose_64: $(OBJ)
	$(MAKE) -o SuperGoose_64 $(OBJ) $(NFD)
test_create: ./testfiles/command_test ./testfiles/die_test ./testfiles/inventory_test ./testfiles/game_test ./testfiles/game_management_test ./testfiles/link_test ./testfiles/set_test ./testfiles/space_test ./testfiles/player_test ./testfiles/object_test

#====================================TESTS====================================#
./testfiles/command_test: ./obj/command_test.o ./obj/command.o
	$(MAKE) -o ./testfiles/command_test ./obj/command_test.o ./obj/command.o

./testfiles/die_test: ./obj/die_test.o ./obj/die.o
	$(MAKE) -o ./testfiles/die_test ./obj/die_test.o ./obj/die.o

./testfiles/inventory_test: ./obj/inventory_test.o ./obj/inventory.o ./obj/set.o
	$(MAKE) -o ./testfiles/inventory_test ./obj/inventory_test.o ./obj/inventory.o ./obj/set.o

./testfiles/game_test: ./obj/game_test.o $(OBJGAME) 
	$(MAKE) -o ./testfiles/game_test ./obj/game_test.o $(OBJGAME) $(NFD)

./testfiles/game_management_test: ./obj/game_management_test.o $(OBJGAME)
	$(MAKE) -o ./testfiles/game_management_test ./obj/game_management_test.o $(OBJGAME) $(NFD)

./testfiles/link_test: ./obj/link_test.o ./obj/link.o ./obj/space.o
	$(MAKE) -o ./testfiles/link_test ./obj/link_test.o ./obj/link.o

./testfiles/set_test: ./obj/set_test.o ./obj/set.o
	$(MAKE) -o ./testfiles/set_test ./obj/set_test.o ./obj/set.o

./testfiles/space_test: ./obj/space_test.o ./obj/space.o ./obj/set.o
	$(MAKE) -o ./testfiles/space_test ./obj/space_test.o ./obj/space.o ./obj/set.o

./testfiles/player_test: ./obj/player_test.o ./obj/player.o ./obj/inventory.o ./obj/set.o
	$(MAKE) -o ./testfiles/player_test ./obj/player_test.o ./obj/player.o ./obj/inventory.o ./obj/set.o

./testfiles/object_test: ./obj/object_test.o ./obj/object.o 
	$(MAKE) -o ./testfiles/object_test ./obj/object_test.o ./obj/object.o 

#===================================OBJECTS===================================#
./obj/command.o: ./src/command.c ./include/command.h ./include/types.h
	$(MAKE) -c ./src/command.c -o ./obj/command.o

./obj/dialogue.o: ./src/dialogue.c ./include/dialogue.h ./include/types.h
	$(MAKE) -c ./src/dialogue.c -o ./obj/dialogue.o 

./obj/die.o: ./src/die.c ./include/die.h ./include/types.h
	$(MAKE) -c ./src/die.c -o ./obj/die.o 

./obj/game.o: ./src/game.c ./include/game.h ./include/types.h ./include/menu.h
	$(MAKE) -c ./src/game.c -o ./obj/game.o

./obj/game_loop.o: ./src/game_loop.c 
	$(MAKE) -c ./src/game_loop.c -o ./obj/game_loop.o

./obj/game_management.o: ./src/game_management.c ./include/game_management.h ./include/types.h ./include/graphic_descriptions.h
	$(MAKE) -c ./src/game_management.c -o ./obj/game_management.o 

./obj/graphic_engine.o: ./src/graphic_engine.c ./include/graphic_engine.h ./include/dialogue.h ./include/types.h
	$(MAKE) -c ./src/graphic_engine.c -o ./obj/graphic_engine.o

./obj/menu.o: ./src/menu.c ./include/menu.h ./include/types.h
	$(MAKE) -c ./src/menu.c -o ./obj/menu.o

./obj/inventory.o: ./src/inventory.c ./include/inventory.h ./include/types.h
	$(MAKE) -c ./src/inventory.c -o ./obj/inventory.o

./obj/link.o: ./src/link.c ./include/link.h ./include/types.h
	$(MAKE) -c ./src/link.c -o ./obj/link.o

./obj/object.o: ./src/object.c ./include/object.h ./include/types.h
	$(MAKE) -c ./src/object.c -o ./obj/object.o

./obj/player.o: ./src/player.c ./include/player.h ./include/types.h
	$(MAKE) -c ./src/player.c -o ./obj/player.o

./obj/screen.o: ./src/screen.c ./include/screen.h ./include/types.h
	$(MAKE) -c ./src/screen.c -o ./obj/screen.o

./obj/set.o: ./src/set.c ./include/set.h ./include/types.h
	$(MAKE) -c ./src/set.c -o ./obj/set.o

./obj/space.o: ./src/space.c ./include/space.h ./include/types.h
	$(MAKE) -c ./src/space.c -o ./obj/space.o

#=================================TESTS OBJECTS=================================#
./obj/command_test.o: ./src/command_test.c
	$(MAKE) -c ./src/command_test.c -o ./obj/command_test.o

./obj/die_test.o: ./src/die_test.c
	$(MAKE) -c ./src/die_test.c  -o ./obj/die_test.o

./obj/game_test.o: ./src/game_test.c
	$(MAKE) -c ./src/game_test.c -o ./obj/game_test.o

./obj/game_management_test.o: ./src/game_management_test.c
	$(MAKE) -c ./src/game_management_test.c -o ./obj/game_management_test.o 

./obj/inventory_test.o: ./src/inventory_test.c
	$(MAKE) -c ./src/inventory_test.c -o ./obj/inventory_test.o

./obj/link_test.o: ./src/link_test.c
	$(MAKE) -c ./src/link_test.c -o ./obj/link_test.o

./obj/set_test.o: ./src/set_test.c
	$(MAKE) -c ./src/set_test.c -o ./obj/set_test.o

./obj/space_test.o: ./src/space_test.c
	$(MAKE) -c ./src/space_test.c -o ./obj/space_test.o

./obj/player_test.o: ./src/player_test.c
	$(MAKE) -c ./src/player_test.c -o ./obj/player_test.o

./obj/object_test.o: ./src/object_test.c
	$(MAKE) -c ./src/object_test.c -o ./obj/object_test.o

#=====================================UTILS=====================================#
run:
	./SuperGoose_64 || true			#This is so that we ensure the makefile doesnt scream when exiting on the menu.

valgrind:
	valgrind -v -q --leak-check=full ./SuperGoose_64 || true

clear:
	rm SuperGoose_64* ./testfiles/* ./obj/*

fclear:
	rm SuperGoose_64* ./testfiles/* ./obj/* DocLink.html
	rm -r ./doc

doxygen:
	doxygen Doxyfile

doxylink:
	ln -sf ./doc/html/index.html DocLink.html

dist:
	tar -czf SuperGoose_64.tgz include src obj doc MEETINGS *file*

test:
	./testfiles/./die_test
	sleep 1
	./testfiles/./set_test
	sleep 1 
	./testfiles/./command_test < ./datafiles/test_command.txt
	sleep 1	
	./testfiles/./game_test < ./datafiles/test_game.txt
	sleep 1
	./testfiles/./game_management_test
	sleep 1 
	./testfiles/./inventory_test
	sleep 1
	./testfiles/./link_test
	sleep 1
	./testfiles/./object_test
	sleep 1
	./testfiles/./player_test
	sleep 1	
	./testfiles/./space_test
	sleep 1
