TARGET=$(wildcard src/*.c)
GO_TARGET=$(wildcard src/*.go)
WININCLUDE=-I /mnt/c/TDM-GCC-64/x86_64-w64-mingw32/include/
WINLIBS=-lmingw32

NAME=maldev01
CC=gcc

all: windows

windows:
	x86_64-w64-mingw32-gcc-9  ${TARGET} ${WININCLUDE} ${WINLIBS} ${WINFLAGS} -mconsole -o  build/Windows/${NAME}.exe

linux:
	${CC} ${TARGET} ${INCLUDE} ${LIBS} ${FLAGS} -o  build/Linux/${NAME}

win_run: windows
	build/Windows/${NAME}.exe

lin_run: linux
	build/Linux/${NAME}

clean:
	rm -rf build/Linux/*
	rm -rf build/Windows/*


