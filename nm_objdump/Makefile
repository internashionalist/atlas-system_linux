CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = hnm
OBJS = hnm.o hnm_funcs32.o hnm_funcs64.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

hnm.o: hnm.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm.c

hnm_funcs32.o: hnm_funcs32.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs32.c

hnmfuncs64.o: hnmfuncs64.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs64.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
