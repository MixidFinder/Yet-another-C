CC=gcc
CFLAGS=-Wall -Werror - Wextra -c
SOURSES=s21_string_test.c s21_string.c
OBJECTS=$(SOURSES.c=.o)
BUILD_DIR=../build

all: strlen_tests strcmp_tests strcpy_tests clang

strlen_tests: 
	$(CC) $(SOURSES) -D Quest_1 $(OBJECTS) -o $(BUILD_DIR)/Quest_1

strcmp_tests: 
	$(CC) $(SOURSES) -D Quest_2 $(OBJECTS) -o $(BUILD_DIR)/Quest_2

strcpy_tests:
	$(CC) $(SOURSES) -D Quest_3 $(OBJECTS) -o $(BUILD_DIR)/Quest_3

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