#Makefile for unit tests
#
# This makefile is seperate from the rest of the build even though
# it can(and is) called from another directory. However because of
# the way it functions, dependencies are not built in, and it
# blindly rebuilds mylib
#
# Makefile gathers all files named suite*.c and concatenates the
# source code into a temporary source called test_functions.c
# Then, the names of the test functions in all the suites are
# found by using objump, and then added to a structure of function
# pointers that is compiled into the source (see generate_tests.sh).
#
# This way one can add any amount of suiteXXX.c files for new test
# suites, and they will be compiled and run. Be aware it will run
# any function that gets compiled into the .text section, so helper
# functions in the suiteXXX.c files are not allowed.
#
# FYI - this was a quick hack to put a rudimenatary unit test
# framework together. The idea was that it was quicker than
# re-learning C-unit. My mileage varied... 
#
# 

PROJECT = ../project2
VPATH = $(PROJECT):../mylib

INCLUDES = -I../mylib
SOURCES = $(wildcard suite*.c)
OBJS := $(SOURCES:%.c=%.o)
OBJS += printf.o

CC ?= gcc
CFLAGS += -Wno-format-extra-args -std=c99 -Wall
LIBS = ../mylib/libmy.a

ifdef DEBUG
CFLAGS += -g
endif

ifeq ($(TARGET),frdm)
    DONT_LINK := -c
    DRIVER :=
else
    DRIVER := driver.o
endif

 

TARGET ?=host
export TARGET

run_tests: test_suite.o test_functions.o $(DRIVER) | test_suites.o
#	make clean-lib -C  $(PROJECT) TARGET=$(TARGET)
#	make libmy.a -C  $(PROJECT) TARGET=$(TARGET)
	$(CC) $(LDFLAGS) -L../mylib/ $(DONT_LINK) $^ -o $@ $(LIBS) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@ 
    

test_functions.c : test_suites.o
	cat suite*.c > test_functions.c
	./generate_tests.sh >> test_functions.c

test_suites.o: $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ 

clean:
	-rm -f *.o test_functions.c run_tests core
