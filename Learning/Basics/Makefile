funcp.o: src/Functionpointer.c
	tcc -c src/Functionpointer.c -o objects/funcp.o

dbg.o: src/Debugmacros.c src/headders/debug.h
	tcc -c src/Debugmacros.c -o objects/dbg.o

forl.o: src/Forloops.c
	tcc -c src/Forloops.c -o objects/forl.o

mapo.h: src\MathPointers.c
	tcc -c .\src\MathPointers.c -o objects/mapo.o


Functionpointer: funcp.o
	tcc objects/funcp.o -o bin/Functionpointer.exe

Forloops: forl.o
	tcc objects/forl.o -o bin/Forloops.exe

Debugmacros: dbg.o
	tcc objects/dbg.o -o bin/Debugmacros.exe

MathPointers: mapo.h
	tcc objects/mapo.o -o .\bin\MathPointers.exe

All: Forloops Functionpointer Debugmacros MathPointers
	
clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\bin" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\objects" /Q
	