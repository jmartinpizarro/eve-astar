CC=g++
CFLAGS=-g -Wall
OBJS=main.o
TARGET=main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(OBJS) $(TARGET)
