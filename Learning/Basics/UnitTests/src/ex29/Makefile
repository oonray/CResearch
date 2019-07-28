all: clean folders
	gcc mylib.c -shared -fPIC -o bin/mylib.so
	gcc main.c -ldl bin/mylib.so -o bin/loader

tests:
	cc unit_test.c -ldl bin/mylib.so -o bin/tests

folders:
	mkdir bin

clean:
	rm -rf bin
