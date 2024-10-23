CC=gcc
CLFLAGS=-Wall -Werror -Wextra -c
SOURSES=dmanager_module.c
OBJ=$(SOURSES.c=.o)
BUILD_DIR=../build

all: door_struct

door_struct:
	$(CC) $(SOURSES) $(OBJ) -o $(BUILD_DIR)/Quest_1

%.o: %.c
	$(CC) $(CLFLAGS) $< -o $@ 

clean:
	rm -f $(OBJECTS)
	rm -f /*.a
	rm -f /*.so
	rm -f $(BUILD_DIR)/*

clang:
	clang-format -i *.c *.h

rebuild: clean all