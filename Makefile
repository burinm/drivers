VPATH = ../mylib

INCLUDES = -I../mylib
SOURCES = $(wildcard suite*.c)
OBJS := $(SOURCES:%.c=%.o)

CC = gcc
LIBS = ../mylib/mylib.a

run_tests: test_functions.o driver.o | test_suites.o
	$(CC) $(CFLAGS) $(INCLUDES) -L../mylib/  $^ -o $@ ../mylib/mylib.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@ 
    

test_functions.c : test_suites.o
	cat suite*.c > test_functions.c
	./generate_tests.sh >> test_functions.c

test_suites.o: $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ 

clean:
	-rm -f driver.o test_suites.o test_functions.c test_functions.o $(OBJS) run_tests core
