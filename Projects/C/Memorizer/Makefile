file = main
libs = -ljson-c -lncurses

all:
	gcc -c src/$(file).c $(libs) -o objects/$(file).o
	gcc objects/$(file).o $(libs) -o bin/memorizer 

dep:
	sudo apt-get install libjson-c-dev

install:

uninstall:

dirs:
	mkdir bin
	mkdir objects

clean:
	rm -rf objects
	rm -rf bin
