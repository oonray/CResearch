
unix: 
	gcc -c main.c -o ./objects/main.o

windows: main.o
	tcc ./objects/main.o -o ./bin/PeParser.exe

main.o: main.c
	tcc -c main.c -o ./objects/main.o

clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\BinaryParser\bin" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\BinaryParser\objects" /Q
	