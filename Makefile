CC=gcc
CFLAGS=-Wall

C_SRC_FILES=$(wildcard src/*.c)
HEADER_FILES=$(wildcard include/*.h)
OBJ_FILES=$(patsubst src/%.c,obj/%.o,$(C_SRC_FILES))

TARGET=chess.x

all: create_dir $(C_SRC_FILES) $(HEADER_FILES) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -I ./include -c $^ -o $@

create_dir:
	mkdir -p obj

clear:
	rm -f *.x
	rm -f -r obj/