# Source files
SRCS = main.c garbage.c funcs.c utils.c

# Object files
OBJS = $(patsubst %.c, %.o, $(SRCS))

# Headers
HEADERS = funcs.h macro.h types.h garbage.h utils.h

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
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Rebuild the library
re: clean all
