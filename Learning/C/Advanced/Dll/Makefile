mylib.o: src/mylib.c
	gcc -c src/mylib.c -o build/objects/mylib.o 

mylib: mylib.o 
	gcc -shared -o build/mylib.so build/objects/mylib.o

loader.o:src/main.c
	gcc -c src/main.c -o build/objects/main.o 

loader: loader.o
	gcc build/objects/main.o -o build/main

all: dirs loader mylib

clean:
	rm build/*
	rm build/objects

