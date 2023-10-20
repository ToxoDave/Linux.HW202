#include "ComplexNumber.h"
#include <algorithm>
#include <vector>

int main(int argc, char** argv)
{	
	std::vector <ComplexNumber> arr(argc - 1);
	for(int i = 1; i < argc; ++i)
	{
		arr[i] = std::stoi(argv[i]);
	}
	std::sort(arr.begin(), arr.end());
	for(int i = 1; i < argc; ++i)
	{
		std::cout << arr[i];
	}
	return 0;
}
