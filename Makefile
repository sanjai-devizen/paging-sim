CC = gcc
CFLAGS = -Wall -Wextra -g -O0
OBJ = main.o alloc.o paging.o error_handling.o
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c defs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)