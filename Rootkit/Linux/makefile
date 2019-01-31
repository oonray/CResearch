
mothership.o: src/main.c
	gcc -c src/main.c -o objects/main.o

obj-m += objects/mothership.o

all:
	make -C `pwd`/bin/`uname -r`/build M=`pwd`/src modules  

clean:
	make -C `pwd`/bin/`uname -r`/build M=`pwd`/src clean