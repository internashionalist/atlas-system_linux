CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g3
INCLUDES = -Iinclude

SRCDIR = src
TARGETS = strace_0 strace_1

all: $(TARGETS)

$(TARGETS): %: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGETS)

re: fclean all

.PHONY: all clean fclean re $(TARGETS)