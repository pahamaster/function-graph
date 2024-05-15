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

print: 
	echo $(O_FILES)
	echo $(C_FILES)

rebuild: clean all

build: $(O_FILES) src/main.o src/graph.o
	$(CC) $(O_FILES) src/main.o src/graph.o -lm -o build/graph

# build: data.o dynamic.o graph.o parsing.o polish.o calculate.o main.o
#	 $(CC) data.o dynamic.o graph.o parsing.o polish.o calculate.o main.o -lm -o ../build/graph

tests:
	$(CC) $(CFLAGS) $(C_FILES) src/test.c $(TEST_FLAGS) -o test
	./test

gcov_report:
	$(CC) -fprofile-arcs -ftest-coverage test.c $(C_FILES) -o gcov_report $(TEST_FLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN_CMD) ./report/index.html

%.o: %.c
	$(CC) -c $(CFLAGSs) $< -o $@

clean:
	rm -f $(O_FILES) test build/graph

#clean:
#	rm -rf *.o *.a *.so *.gcda *.gcno *.info test gcov_report report

