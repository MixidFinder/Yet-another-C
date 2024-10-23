CC=gcc
CFLAGS=-Wall -Werror -Wextra -c
LDFLAGS=-L../data_libs -L../data_module
SOURSES=$(wildcard ../data_module/data_process.c ../yet_another_decision_module/decision.c ../data_libs/*.c main_executable_module.c)
OBJECTS=$(SOURSES:.c=.o)
STATIC=$(filter-out ../data/libs/data_stat.o, $(OBJECTS))
DYNAMIC=$(filter-out ../data_module/data_process.o ../data_libs/data_stat.o, $(OBJECTS))
EXECUTABLE=Quest_3
BUILD_DIR=../../build

all: $(EXECUTABLE) build_with_static

build_with_static: data_stat.a $(STATIC)
	$(CC) $(LDFLAGS) -ldata_stat $(STATIC) -o $(BUILD_DIR)/Quest_5

data_stat.a: ../data_libs/data_stat.o
	ar rcs ../data_libs/lib$@ $^

build_with_dynamic:


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f ../*/*.a
	rm -f ../*/*.so
	rm -f $(BUILD_DIR)/*

rebuild: clean all