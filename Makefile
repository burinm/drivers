VPATH = ../mylib

INCLUDES = -I../mylib
SOURCES = $(wildcard suite*.c)
OBJS := $(SOURCES:%.c=%.o)

CC = gcc
LIBS = ../mylib/mylib.a

run_tests: test_functions.c driver.c | test_suites.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

test_functions.c : test_suites.o
	cat suite*.c > test_functions.c
	./generate_tests.sh >> test_functions.c

test_suites.o: $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@ 

clean:
	-rm -f test_suites.o test_functions.c $(OBJS) run_tests core
