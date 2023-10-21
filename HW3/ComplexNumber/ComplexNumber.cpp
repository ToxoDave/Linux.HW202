#include "ComplexNumber.h"
#include <iostream>
#include <cmath>

ComplexNumber :: ComplexNumber() {}
ComplexNumber :: ComplexNumber(double real, double im) : a(real), b(im) {}
ComplexNumber :: ComplexNumber(double real) : a(real) {}
std::ostream& operator<< (std::ostream out, const ComplexNumber& c)
{
        return out << c.a << "+ i *" << c.b;
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
double getModule(const ComplexNumber& c)
{
	return sqrt(c.a * c.a + c.b * c.b);
}
