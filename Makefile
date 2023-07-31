# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -std=c11

# Source files and executables
SRCS := main.c functions.c readFile_randWord.c
OBJS := $(SRCS:.c=.o)
EXECUTABLE := my_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
