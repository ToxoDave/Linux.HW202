#include <iostream>
#include <vector>
#include <string>
#include <climits>

int main(int argc, char** argv)
{
	int max = INT_MIN, min = INT_MAX;
	for(int i = 1; i < argc; ++i)
	{
		int tmp = std::stoi(argv[i]);
		if(tmp > max)
		{
			max = tmp;
		}
		if(tmp < min)
		{
			min = tmp;
		}
	}
	std::cout << "max is " << max << "\nmin is " << min << std::endl;
}
