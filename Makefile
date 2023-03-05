CC=gcc
CFLAGS=-Wall

C_SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o,$(C_SRC))

TARGET=chess.x

all:$(OBJ)
	$(CC) $^ -o $(TARGET)

obj/%.o:src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	rm *.x
	rm obj/*.o