$CC=gcc
CFLAGS= -g -O2 -Wall -Isrc -rdynamic -DNDEBUG $(OPTFLAGS) 
PREFIX?=/usr/local

LDLIBS=-ldl -lbsd -lm $(OPTLIBS)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o, $(SOURCES))

PROGRAMS_SRC=$(wildcard bin/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAMS_SRC))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%, $(TEST_SRC))

NAME=lcthw
TARGET=build/lib$(NAME).a
SO_TARGET=$(patsubst %.a,%.so, $(TARGET))

all: flags $(TARGET) $(SO_TARGET) tests $(PRORAMS)

flags:
	@echo "$(CFLAGS)" | sed -r "s: :\n:g" >  compile_flags.txt

dev: CFLAGS= -g -Wall -Isrc -W all -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(PROGRAMS): CFLAGS += $(TARGET)

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS) 

build:
	@mkdir -p build
	@mkdir -p bin

.PHONY: test
tests: CFLAGS+=$(SO_TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

clean:
	rm -rf build $(OBJECTS) $(TESTS) $(PROGRAMS)
	rm -rf tests/tests.log
	rm -rf compile_flags.txt
	find . -name "*.gc*" -delete
	rm -rf `find . -name "*.dSYM" -print`

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
