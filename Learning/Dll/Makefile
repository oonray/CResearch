mylib.o: src/mylib.c src/headders/debug.h src/headders/colors.h
	gcc -c src/mylib.c -o build/objects/mylib.o 

mylib: build/objects/mylib.o 
	gcc -shared -o build/mylib.so build/objects/mylib.o

loader.o:src/main.c src/headders/debug.h src/headders/colors.h
	gcc -c src/main.c -o build/objects/main.o 

loader: loader.o
	gcc build/objects/main.o -o build/main

all: loader mylib

clean:
	rm -rf build/*

