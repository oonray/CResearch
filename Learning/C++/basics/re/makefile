FLAGS=-O3 -std=c++2a -Wall -Wextra
all:
	gcc src/main.cpp $(FLAGS)  -o re

flags:
	echo $(FLAGS) | tr " " "\n" > compile_flags.txt
	./re
