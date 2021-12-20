CC = gcc
C_FLAGS = -Wall -Wextra
SOURCES = work.c

all: work debug run clean

work:
	$(CC) $(SOURCES) $(C_FLAGS) -o work
debug:
	$(CC) -g $(SOURCES)
run:
	./work
clean:
	rm work

