# Source files
SRCS = $(wildcard ./src/*.c)

# Object files
OBJS = $(patsubst ./src/%.c, ./obj/%.o, $(SRCS))

# Headers
HEADERS = $(wildcard ./headers/*.h)

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -g -Ofast -fsanitize=address

# Name of the static library
NAME = nn

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile .c files into .o files
./obj/%.o: ./src/%.c $(HEADERS)
	mkdir -p ./obj
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -rf ./obj $(NAME)

# Phony targets
.PHONY: all clean