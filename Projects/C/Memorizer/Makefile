file = main
libs = json-c

all: dirs
	gcc -c src/$(file).c -l $(libs) -o objects/$(file).o
	gcc objects/$(file).o -o bin/memorizer 

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
