run: main
	./main

main.o:	main.cpp
	g++ main.cpp -c

complex_number.o: ComplexNumber.cpp ComplexNumber.h
	g++ ComplexNumber.cpp -c

main:   main.o complex_number.o
	g++ main.o ComplexNumber.o -o main
