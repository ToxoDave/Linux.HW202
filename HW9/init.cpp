#include <iostream>
#include <cerrno>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{	
	const int size = 4096;
	const char* shm_name = "/my_shm";
	int shd = shm_open(shm_name, O_RDWR | O_CREAT, 0666);
	if(shd == -1)
	{
		perror("Cant shmopen");
		exit(errno);
	}	

	if(ftruncate(shd, size) == -1)
	{
		perror("Cant ftruncate");
		exit(errno);
	}
	
	void* mmap_res = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shd, 0);
	if(mmap_res == MAP_FAILED)
	{
		perror("Cant mmap");
		exit(errno);
	}

	int* sharr = static_cast<int*>(mmap_res);

	for(int i = 0; i < 1024; ++i)
	{	
		sharr[i] = 0;
	}

	close(shd);
	return 0;
}
