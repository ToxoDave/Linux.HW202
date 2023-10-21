run: main
	./main

main.o:	main.cpp
	g++ main.cpp -c

complex_number.o: ComplexNumber.cpp ComplexNumber.h
	g++ ComplexNumber.cpp -c

main:   main.o ComplexNumber.o
	g++ main.o ComplexNumber.o -o main

clean:
	rm -f main.o ComplexNumber.o 
