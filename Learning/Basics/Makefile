funcp.o: src/Functionpointer.c
	tcc -c src/Functionpointer.c -o objects/funcp.o

Functionpointer: funcp.o
	tcc objects/funcp.o -o bin/Functionpointer.exe

forl.o: src/Forloops.c
	tcc -c src/Forloops.c -o objects/forl.o

Forloops: forl.o
	tcc -c objects/forl.o -o bin/Forloops.exe

dbgm.o: src/Debugmacros.c
	tcc -c src/Debugmacros.c -o objects/dbgm.o

Debugmacros: dbgm.o
	tcc -c objects/dbgm.o -o bin/Debugmacros.exe

MathPointers:
	tcc .\src\MathPointers.c -o .\bin\MathPointers.exe

All: Forloops Functionpointer Debugmacros MathPointers
	
clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\bin" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Learning\objects" /Q
	