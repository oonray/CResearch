obj-m += mothership.o

all:
	make -C `pwd`/bin/`uname -r`/build M=`pwd`/src modules  

clean:
	make -C `pwd`/bin/`uname -r`/build M=`pwd`/src clean