# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g -Iinclude -std=gnu99

# Directories
SRC_DIR = src
TASK0_DIR = $(SRC_DIR)/task0

# Common & Task-Specific Source Files
COMMON_SRC = $(wildcard $(SRC_DIR)/*.c)
TASK0_SRC = $(wildcard $(TASK0_DIR)/*.c)

# All Source Files
0_SRC = $(COMMON_SRC) $(TASK0_SRC)

# Object File
OBJ = $(patsubst %.c,%.o,$(0_SRC))

# Output Executable
EXEC = 0-hreadelf

# All Target
all: $(EXEC)

# Build Executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Compile Source Files into Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

# Include Dependency Files
-include $(OBJ:.o=.d)

# Clean All Object Files and Executables
clean:
	rm -f $(OBJ) $(EXEC) $(OBJ:.o=.d)
