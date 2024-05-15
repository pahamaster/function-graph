CC = gcc
TEST_FLAGS = $(shell pkg-config --cflags --libs check)
CFLAGS= -Wall -Werror -Wextra
OS := $(shell uname -s)

C_FILES = src/polish.c src/dynamic.c src/parsing.c src/calculate.c src/data.c
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

ALL_C_FILES = $(wildcard ./src/*.c)


ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: build

rebuild: clean all

build: $(O_FILES) src/main.o src/graph.o
	$(CC) $(O_FILES) src/main.o src/graph.o -lm -o build/graph

tests:
	$(CC) $(CFLAGS) $(C_FILES) src/test.c $(TEST_FLAGS) -o test
	valgrind --leak-check=full -s --track-origins=yes ./test

gcov_report:
	$(CC) -fprofile-arcs -ftest-coverage src/test.c $(C_FILES) -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html

%.o: %.c
	$(CC) -c $(CFLAGSs) $< -o $@

clean:
	rm -f $(O_FILES) test build/graph *.gcda *.gcno *.info gcov_report
	rm -rf report
