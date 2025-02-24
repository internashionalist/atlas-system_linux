# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g -Iinclude -std=gnu99

# Files
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=%.o)

# Output executable
EXEC = 0-hreadelf

# All target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Compile source files into object files
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

# Include dependencies
-include $(OBJ:.o=.d)

# Clean object and executable files
clean:
	rm -f $(OBJ) $(EXEC) *.d
