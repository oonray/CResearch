CC=gcc
TEST_FLAGS=-lrt -lm -lvector -Isrc 

$CC=gcc
CFLAGS= -g -O2 -Wall -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
PREFIX?=/usr/local

LDLIBS=-ldl -lm -lvector $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TEST_SRC+=tests/munit.c

TESTS=$(patsubst %.c,%, $(TEST_SRC))

NAME=map
TARGET=build/lib$(NAME).a
SO_TARGET=$(patsubst %.a,%.so, $(TARGET))

all:$(TARGET) $(SO_TARGET) tests

dev: CFLAGS= -g -Wall -Isrc -W all -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build

.PHONY: test
tests:
	$(CC) $(TEST_FLAGS) $(TEST_SRC $(SOURCES) -o build/$(name)_test

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -rf tests/tests.log
	rm -rf compile_flags.txt
	find . -name "*.gc*" -delete
	rm -rf `find . -name "*.dSYM" -print`

install: all
	sudo mkdir -p /usr/local/include/c/
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib
	cp $(shell pwd)/src/*.h /usr/local/include/c/

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
