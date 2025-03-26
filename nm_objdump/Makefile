CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = hnm

all: $(TARGET)

$(TARGET): hnm.o hnm_funcs32.o hnm_funcs64.o
	$(CC) $(CFLAGS) -static -o $(TARGET) hnm.o hnm_funcs32.o hnm_funcs64.o

hnm.o: hnm.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm.c

hnm_funcs32.o: hnm_funcs32.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs32.c

hnm_funcs64.o: hnm_funcs64.c hnm_funcs.h
	$(CC) $(CFLAGS) -c hnm_funcs64.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
