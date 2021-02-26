CC=gcc
PREFIX?=/usr/local

TEST_FLAGS=-lrt -L$(PREFIX)/lib/ -lm -Isrc 

CFLAGS= -g -O2 -Wall -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)

LIBS=-ldl -L$(PREFIX)/lib/ $(OPTLIBS)
LDLIBS=-ldl -lm -L$(PREFIX)/lib/ $(OPTLIBS)


SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_SRC+=tests/munit.c

TESTS=$(patsubst %.c,%, $(TEST_SRC))

NAME=vector
TARGET=build/lib$(NAME).a
SO_TARGET=$(patsubst %.a,%.so, $(TARGET))

all:$(TARGET) $(SO_TARGET) unitests

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

.PHONY: test
unitests:
	$(CC) $(TEST_FLAGS) $(TEST_SRC) -lvector -o bin/$(NAME)_test
	/bin/bash -c bin/$(NAME)_test

clean:
	rm -rf build bin $(OBJECTS) $(TESTS)
	rm -rf compile_flags.txt
	find . -name "*.gc*" -delete
	rm -rf `find . -name "*.dSYM" -print`

install: all
	mkdir -p /usr/local/include/c/
	install -d $(DESTDIR)$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)$(PREFIX)/lib
	cp $(shell pwd)/src/*.h /usr/local/include/c/

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
