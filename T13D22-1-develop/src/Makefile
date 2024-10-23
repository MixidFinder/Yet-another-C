CC=gcc
CFLAGS=-Wall -Werror - Wextra -c
SOURSES=cipher.c
OBJECTS=$(SOURSES.c=.o)
BUILD_DIR=../build

all: cipher

cipher: 
	$(CC) $(SOURSES) $(OBJECTS) -o $(BUILD_DIR)/cipher


%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f /*.a
	rm -f /*.so
	rm -f $(BUILD_DIR)/*

clang:
	clang-format -i *.c *.h

rebuild: clean all