all:
	gcc --shared DLL/dll01.c -o build/libdll01.so
	gcc --shared DLL/dll02.c -o build/libdll02.so
	
	gcc Program/main.c -o build/program -L build -l dll01
	gcc Runner/main.c -o build/runner -L build -l dll01
clean:
	rm build/*