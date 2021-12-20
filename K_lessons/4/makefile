CC = gcc
CFLAGS = -Wextra -Wall -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -I./include/ 
SOURCES = *.c

all: main run clean

main:
	$(CC) $(SOURCES) $(CFLAGS) -o main

debug:
	$(CC) -g $(SOURCES) $(CFLAGS)
run:
	./main

clean:
	rm main