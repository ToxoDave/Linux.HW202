#include "ComplexNumber.h"
#include <iostream>
#include <cmath>

ComplexNumber::ComplexNumber() {}
ComplexNumber::ComplexNumber(double real, double im) : a(real), b(im) {}
ComplexNumber::ComplexNumber(double real) : a(real) {}
std::ostream& operator<< (std::ostream& out, const ComplexNumber& c)
{
	if(c.a != 0 && c.b != 0)
	{
        	return out << c.a << " + " << c.b << "i";
	}
	else if(c.a == 0 && c.b != 0)
	{
		return out << c.b << "i";
	}
	else if(c.b == 0 && c.a != 0)
	{
		return out << c.a;
	}
	return out << "0";
}

ComplexNumber operator+(const ComplexNumber& c1, const ComplexNumber& c2)
{
        ComplexNumber result{c1.a + c2.a, c1.b + c2.b};
        return result;
}

ComplexNumber operator-(const ComplexNumber& c1, const ComplexNumber& c2)
{
        ComplexNumber result{c1.a - c2.a, c1.b - c2.b};
        return result;
}

ComplexNumber operator*(const ComplexNumber& c, double k)
{
        ComplexNumber result{c.a * k, c.b * k};
        return result;
}
double ComplexNumber::getModule() const
{
	return sqrt(a * a + b * b);
}

