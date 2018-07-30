linux: 
windows: main.o
	tcc objects/main.o -o bin/windows/StudentTracker.exe
apple:

main.o: src/main.c src/inc/constants.h src/inc/debug.h src/argparser.c
	tcc -c src/main.c -o objects/main.o

clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Windows" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Apple" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Linux" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\objects" /Q
	