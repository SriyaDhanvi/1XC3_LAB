CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm -lsodium

SRC_FILES = constants.h mymodel.h mymodel.c main.c
OBJ_FILES = mymodel.o main.o
EXECUTABLE = neural_network

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

mymodel.o: mymodel.c mymodel.h
	$(CC) $(CFLAGS) -c mymodel.c -o mymodel.o

main.o: main.c mymodel.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -rf $(OBJ_FILES) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
