FILES=$(wildcard src/*.c)
INCLUDES=-I /mnt/c/TDM-GCC-64/x86_64-w64-mingw32/include/

all: linux

windows:
	x86_64-w64-mingw32-gcc ${FILES} ${INCLUDES} ${LIBS} -o build/windows/proxy.exe

linux:
	gcc ${FILES} ${LIBS} -o build/linux/proxy

