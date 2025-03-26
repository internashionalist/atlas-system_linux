CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = hnm

all: $(TARGET)

$(TARGET): main.o hnm_funcs.o hnm_funcs32.o
	$(CC) $(CFLAGS) -static -o $(TARGET) main.o hnm_funcs.o hnm_funcs32.o

main.o: main.c hnm_funcs.h
	$(CC) $(CFLAGS) -c main.c

hnm_funcs.o: hnm_funcs.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs.c

hnm_funcs32.o: hnm_funcs32.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs32.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
