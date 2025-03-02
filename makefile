CC=g++
CFLAGS=-g -Wall
OBJS=main.o
TARGET=main
ROUTE=src/

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: $(ROUTE)main.cpp
	$(CC) $(CFLAGS) -c $(ROUTE)main.cpp -o main.o

clean:
	rm -f $(OBJS) $(TARGET)
