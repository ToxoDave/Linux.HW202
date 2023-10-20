#ifndef	ComplexNumber_h
#define	ComplexNumber_h

#include <iostream>

class ComplexNumber
{
public:
	double a = 0;
	double b = 0;

	ComplexNumber();
	ComplexNumber(double real);
	ComplexNumber(double real, double im);
	bool operator<(const ComplexNumber& other);
	friend std::ostream& operator<<(std::ostream& out, const ComplexNumber& c);
	friend ComplexNumber operator+(const ComplexNumber& c1, const ComplexNumber& c2);
	friend ComplexNumber operator-(const ComplexNumber& c1, const ComplexNumber& c2);
	friend ComplexNumber operator*(const ComplexNumber& c, double k);
	friend double getModule();

};


#endif
