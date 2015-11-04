CC=g++
CFLAGS=-Wall --std=c++11
SFML=-lsfml-graphics -lsfml-window -lsfml-system
OBJECTS=main.o graphics.o chip-8.o exceptions.o keys.o
OUTPUT=bun-8

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(SFML) $(OBJECTS) -o $(OUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) -c graphics.cpp -o graphics.o

chip-8.o: chip-8.cpp chip-8.h
	$(CC) $(CFLAGS) -c chip-8.cpp -o chip-8.o

exceptions.o: exceptions.cpp exceptions.h
	$(CC) $(CFLAGS) -c exceptions.cpp -o exceptions.o

keys.o: keys.cpp keys.h
	$(CC) $(CFLAGS) $(SFML) -c keys.cpp -o keys.o
clean:
	rm $(OBJECTS)
	rm bun-8
