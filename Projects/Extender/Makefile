
SOURCES=$(wildcard src/**/*.c src/*.c)

TARGET=bin/extender.exe
all:
	gcc $(SOURCES) -o $(TARGET)

build:
	@mkdir -p build
	@mkdir -p bin
	
clean:
	rm -rf build $(OBJECTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print

check:
	@echo Files With potentially dangerous functions
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok_)|stpn?cpy|s?sn?printf|byte_)' $(SOURCES) || true
