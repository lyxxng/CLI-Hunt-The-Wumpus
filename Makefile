CC = g++ -std=c++11 -g -lncurses
exe_file = hunt_wumpus

all: $(exe_file)

$(exe_file): room.o event.o rope.o bats.o gold.o pit.o wumpus.o game.o main.cpp
	$(CC) room.o event.o rope.o bats.o gold.o pit.o wumpus.o game.o main.cpp -o $(exe_file)

room.o: room.cpp room.h
	$(CC) -c room.cpp

event.o: event.cpp event.h
	$(CC) -c event.cpp

rope.o: rope.cpp rope.h
	$(CC) -c rope.cpp

bats.o: bats.cpp bats.h
	$(CC) -c bats.cpp

gold.o: gold.cpp gold.h
	$(CC) -c gold.cpp

pit.o: pit.cpp pit.h
	$(CC) -c pit.cpp

wumpus.o: wumpus.cpp wumpus.h
	$(CC) -c wumpus.cpp

game.o: game.cpp game.h
	$(CC) -c game.cpp

clean:
	rm -f *.out *.o $(exe_file)