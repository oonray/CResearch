linux: src/main.c db_func.o
	tcc src/main.c objects/db_func.o  -o bin/Linux/StudentTracker
	chmod +x bin/Linux/StudentTracker
windows: src/main.c db_func.o
	tcc src/main.c objects/db_func.o  -o bin/Windows/StudentTracker.exe
apple:

db_func.o:src/db_func.c src/inc/constants.h src/inc/debug.h
	tcc -c src/db_func.c -o objects/db_func.o

clean:
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Windows" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Apple" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\bin\Linux" /Q
	del "D:\OneDrive - Noroff Education AS\R&D\CResearch\Projects\StudentTracker\objects" /Q
	