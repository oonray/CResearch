obj-m += mothership.o

all:
	make -c bin/`uname -r`/build M=`pwd` modules  

clean:
	make -c bin/`uname -r`/build M=`pwd` clean