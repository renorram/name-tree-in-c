TARGET = main
CC=gcc
CFLAGS =-I. -Wall -Wextra -Werror
HEADERS = name_tree.h tree.h reader.h
OBJ = main.o tree.o reader.o name_tree.o

.PHONY: clean

%.o : %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm ./$(TARGET) *.o
