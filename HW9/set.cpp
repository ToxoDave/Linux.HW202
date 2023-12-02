#include <iostream>
#include <cerrno>
#include <algorithm>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cmath>

void eratosphenes_sieve(int* arr, int max_size)
{
	for(int i = 0; i < max_size; ++i)
	{
		arr[i] = 1;
	}
	arr[0] = 0;
	arr[1] = 0;
	for(int j = 2; j <= static_cast<int>(std::sqrt(max_size)); ++j)
	{
		if(arr[j] == 1)
		{
			for(int k = j * j; k < max_size; k += j)
			{
				arr[k] = 0;
			}
		}
	}
}

int main()
{
	const int size = 4096;
	const char* shm_name = "/my_shm";

	int shd = shm_open(shm_name, O_RDWR, 0666);
	if(shd == -1)
	{
		perror("Cant shmopen");
		exit(errno);
	}

	/*int* shared_array = static_cast<int*>(mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shd, 0));
	if(shared_array = MAP_FAILED)
	{
		perror("Cant mmap");
		exit(errno);
	}
	*/

	void* mmap_res = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shd, 0);
        if(mmap_res == MAP_FAILED)
        {
                perror("Cant mmap");
                exit(errno);
        }

	int* sharr = static_cast<int*>(mmap_res);
	eratosphenes_sieve(sharr, size / 4);

	close(shd);
	return 0;
}
