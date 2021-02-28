CC=gcc
AR=ar
RANLIB=ranlib
PREFIX?=/usr/local
MINGWPREFIX=/mnt/f/lib/SDL2/SDL2-2.0.14/x86_64-w64-mingw32/

TEST_FLAGS=-lrt -lm -Isrc 
CFLAGS=-g -O2 -Wall -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl  $(OPTLIBS)
LDLIBS=-ldl -lm $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o, $(SOURCES))
MINOBJECTS=$(patsubst %.o,%.mingw.o, $(OBJECTS))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_SRC+=tests/munit.c

TESTS=$(patsubst %.c,%, $(TEST_SRC))

NAME=vector
TARGET=build/lib$(NAME).a
MINTARGET=build/lib$(NAME).mingw.a
SO_TARGET=$(patsubst %.a,%.so, $(TARGET))
MIN_SO_TARGET=$(patsubst %.a,%.so, $(MINTARGET))

all:build unitests

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

build:
	@mkdir -p build
	@mkdir -p bin

.PHONY: test
unitests:
	$(CC) $(TEST_SRC) $(TEST_FLAGS) -o bin/$(NAME)_test
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
