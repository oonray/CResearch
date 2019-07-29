#Findfaces
#May 3, 2018
#Dan Gookin

# if the code doesn't compile with the libjpeg or libcurl libraries, ensure
# that you add the proper -L and -I switches to the first clang command
# such as: -I/usr/local/curl/include -L/usr/local/curl/lib

findfaces : main.o watson.o do_jpeg.o
	clang -Wall -lcurl -ljpeg main.o watson.o do_jpeg.o -o findfaces

main.o: main.c findfaces.h
	clang -c main.c

watson.o: watson.c findfaces.h
	clang -c watson.c

dojpeg.o: do_jpeg.c findfaces.h
	clang -c do_jpeg.c

