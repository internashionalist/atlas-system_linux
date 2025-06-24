CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -pedantic -std=gnu89
OBJS    := 4-rest.o
TARGET  := todo_api_0

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c sockets.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
