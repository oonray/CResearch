CC=gcc
AR=ar
RANLIB=ranlib
PREFIX?=/usr/local
MINGWPREFIX=/mnt/f/lib/SDL2/SDL2-2.0.14/x86_64-w64-mingw32/

TEST_FLAGS=-lrt -lm -Isrc 
CFLAGS=-g -O2 -Wall -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-L /usr/local/lib -ldl $(OPTLIBS)
LDLIBS=-ldl -lm $(OPTLIBS)

OBJECTS=$(patsubst %.c,%.o, $(SOURCES))
MINOBJECTS=$(patsubst %.o,%.mingw.o, $(OBJECTS))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_SRC+=tests/munit.c

TESTS=$(patsubst %.c,%, $(TEST_SRC))

NAME=map
TARGET=build/lib$(NAME).a
SO_TARGET=$(patsubst %.a,%.so, $(TARGET))

all:build unitests

build:
	@mkdir -p build
	@mkdir -p bin

.PHONY: test
unitests:
	$(CC) $(TEST_SRC) $(TEST_FLAGS) $(LIBS) -o bin/$(NAME)_test
	/bin/bash -c bin/$(NAME)_test

clean:
	rm -rf build bin $(OBJECTS) $(MINOBJECTS) $(TESTS)
	rm -rf compile_commands.json
	find . -name "*.gc*" -delete
	rm -rf `find . -name "*.dSYM" -print`
	rm -rf .ccls-cache .clangd

install: all
	mkdir -p /usr/local/include/c/
	cp $(shell pwd)/src/*.h /usr/local/include/c/

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
