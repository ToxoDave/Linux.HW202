#include "ComplexNumber.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char** argv)
{	
	std::vector <ComplexNumber> arr = { {5, 8}, {3, 0}, {0, 8}, {2.6, 4}};

	std::sort(arr.begin(), arr.end());
	for(int i = 1; i < argc; ++i)
	{
		std::cout << arr[i] << " ";
	}
	return 0;
}

/* [](const ComplexNumber& c1, const ComplexNumber& c2) { return c1.getModule(c1) < c2.getModule(c2); });*/

