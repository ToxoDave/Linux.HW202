#include <iostream>
#include <sys/mman.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <exception>

bool IsPrime(int* arr, int max_size, int num)
{
	if(num >= max_size)
	{
		perror("Cant access");
		exit(errno);
	}
	else
	{ return (arr[num] == 1); }
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		perror("ERROR");
		exit(errno);
	}
	const int size = 4096;
	const char* shm_name = "/my_shm";
	int N = std::stoi(argv[1]);
	
	int shd = shm_open(shm_name, O_RDWR, 0666);
	if(shd == -1)
	{
		perror("Cant open");
		exit(errno);
	}

	void* mmap_res = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shd, 0);
	if(mmap_res == MAP_FAILED)
	{
		perror("Cant mmap");
		exit(errno);
	}

	int* sharr = static_cast<int*> (mmap_res);

	if(IsPrime(sharr, size / 4, N))
	{
		std::cout << N << " Is prime";
	}
	else{ 
		std:: cout << N << " Isn't prime";
	}
	std::cout << std::endl;
	return 0;
}
