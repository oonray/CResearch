all:
	gcc --shared DLL/dll01.c -o build/libdll01.so
	gcc --shared DLL/dll02.c -o build/libdll02.so
	gcc Loader/main.c -o build/loader
	gcc Program/main.c -o build/program -L build -l dll01

clean:
	rm build/*