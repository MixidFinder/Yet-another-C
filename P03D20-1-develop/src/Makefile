BUILD_DIR = ../build/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

# Default target to build both executables
all: graph  #remove clang before revue

# Source files
SRC_FILES_Q1 = graph.o data_io.o data_parse.o polish_notation.o dynamic_stack.o

# Targets for executables
TARGET = $(BUILD_DIR)graph

# Build target
graph: $(SRC_FILES_Q1)
	$(CC) $(CFLAGS) $(SRC_FILES_Q1) -o $(TARGET)

# Object files
graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c -o graph.o

data_io.o: data_io.c
	$(CC) $(CFLAGS) -c data_io.c -o data_io.o	

data_parse.o: data_parse.c
	$(CC) $(CFLAGS) -c data_parse.c -o data_parse.o	

polish_notation.o: polish_notation.c
	$(CC) $(CFLAGS) -c polish_notation.c -o polish_notation.o	

dynamic_stack.o: dynamic_stack.c
	$(CC) $(CFLAGS) -c dynamic_stack.c -o dynamic_stack.o	


# Target to clang-format all
clang:
	@if [ ! -f .clang-format ]; then \
		echo "Error: .clang-format file not found in current directory"; \
		if [ -f ../materials/linters/.clang-format ]; then \
			cp ../materials/linters/.clang-format . && echo ".clang-format file successfully copied." || { echo "Error: Failed to copy .clang-format"; exit 1; }; \
		else \
			echo "Error: .clang-format file not found in ../materials/linters"; \
			exit 1; \
		fi; \
	fi; \
	find . -name '*.c' -o -name '*.h' | xargs clang-format -i && echo "Clang formatting completed successfully." || echo "Error: Formatting failed."

# Clean up built files
clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
