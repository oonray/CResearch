all: clean folders
	gcc mylib.c -shared -fPIC -o bin/mylib.so
	gcc main.c -ldl bin/mylib.so -o bin/loader
	gcc unit_test.c -ldl -o bin/tests

tests:
	cc unit_test.c -ldl bin/mylib.so -o bin/tests

folders:
	mkdir bin

clean:
	rm -rf bin
