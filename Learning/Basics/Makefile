funcp.o: src/Functionpointer.c
	tcc -c src/Functionpointer.c -o objects/funcp.o

dbg.o: src/Debugmacros.c src/headders/debug.h
	tcc -c src/Debugmacros.c -o objects/dbg.o

forl.o: src/Forloops.c
	tcc -c src/Forloops.c -o objects/forl.o

mapo.h: src\MathPointers.c
	tcc -c .\src\MathPointers.c -o objects/mapo.o

io.o: src/IOFiles.c
	tcc -c ./src/IOFiles.c -o objects/io.o

files.o: src/Files.c
	gcc -c -o objects/files.o src/files.c

Functionpointer: funcp.o
	tcc objects/funcp.o -o bin/Functionpointer.exe

Forloops: forl.o
	tcc objects/forl.o -o bin/Forloops.exe

Debugmacros: dbg.o
	tcc objects/dbg.o -o bin/Debugmacros.exe

MathPointers: mapo.h
	tcc objects/mapo.o -o .\bin\MathPointers.exe

global.o: src/headders/debug.h src/headders/globals.h
	tcc -c src/globals1.c -o objects/global1.o

Globals: global.o
	tcc src/globals_main.c objects/global1.o -o bin/global.exe

IOFiles: io.o
	tcc objects/io.o -o bin/IOFiles

Files: files.o
	gcc -o bin/Files objects/files.o

All: Forloops Functionpointer Debugmacros MathPointers
	
clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\bin" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\objects" /Q
	
