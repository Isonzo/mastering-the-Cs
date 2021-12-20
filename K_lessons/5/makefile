CC = gcc
CFLAGS = -Wextra -Wall -I./include/
SOURCES = main.c stream.c

all: main run clean

main:
	$(CC) $(SOURCES) $(CFLAGS) -o main

debug:
	$(CC) -g $(SOURCES) $(CFLAGS)
run:
	./main

clean:
	rm main