#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char** argv)
{	
	std::vector<int> v(argc);
	for(int i = 1; i < v.size(); ++i)
	{
		v[i - 1] = std::stoi(argv[i]);
	}
	std::reverse(v.begin(), v.end());
	for(int i = 1; i < v.size(); ++i)
	{
		std::cout << v[i];
	}
return 0;
}

