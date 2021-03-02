
TARGET=$(wildcard src/*.c)
GO_TARGET=$(wildcard src/*.go)
WININCLUDE=-I /mnt/f/cygwin64/usr/i686-w64-mingw32/sys-root/mingw/include -I /usr/local/include
WINLIBS=-lmingw32 
WINFLAGS=-w -Wl,-subsystem,console -mconsole
NAME=maldev01
CC=x86_64-w64-mingw32-gcc-9

all: windows

windows:
	$(CC)  $(TARGET) $(WININCLUDE) $(WINLIBS) $(WINFLAGS) -o  build/${NAME}.exe

win_run: windows
	build/Windows/${NAME}.exe

clean:
	rm -rf build/*


