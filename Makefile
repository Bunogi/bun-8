CC=g++
CFLAGS=-Wall --std=c++11
SFML=-I/usr/include -lsfml-graphics -lsmfl-window -lsmfl-system
LIBS=
OBJECTS=main.o graphics.o chip-8.o exceptions.o
OUTPUT=bun-8

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(SFML) $(OBJECTS) -o $(OUTPUT)

main.o: main.cpp
	$(CC) $(CFLAGS) $(LIBS) -c main.cpp -o main.o

graphics.o: graphics.cpp
	$(CC) $(CFLAGS) $(LIBS) $(SFML) -c graphics.cpp -o graphics.o

chip-8.o: chip-8.cpp
	$(CC) $(CFLAGS) $(LIBS) -c chip-8.cpp -o chip-8.o

exceptions.o: exceptions.cpp
	$(CC) $(CFLAGS) $(LIBS) -c exceptions.cpp -o exceptions.o

clean:
	rm $(OBJECTS)
	rm bun-8
