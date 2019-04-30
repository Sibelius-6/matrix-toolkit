main: main.o matrix.o sqrt.o fraction.o complex.o
	g++-5 -std=c++14 -Wall main.o matrix.o sqrt.o fraction.o complex.o -o main

sqrt.o: sqrt.cc sqrt.h
	g++-5 -std=c++14 -Wall -c sqrt.cc
fraction.o: fraction.cc fraction.h sqrt.h
	g++-5 -std=c++14 -Wall -c fraction.cc
complex.o: complex.cc complex.h fraction.h
	g++-5 -std=c++14 -Wall -c complex.cc
matrix.o: matrix.cc matrix.h complex.h
	g++-5 -std=c++14 -Wall -I eigen/ -c matrix.cc
main.o: matrix.h complex.h main.cc
	g++-5 -std=c++14 -Wall -c main.cc
