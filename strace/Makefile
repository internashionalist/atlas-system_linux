CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
NAME = strace_0
SRC = src/strace_0.c
OBJ = $(SRC:.c=.o)
INCLUDES = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -static -o $(NAME) $(OBJ) $(INCLUDES)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
