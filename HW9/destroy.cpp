#include <iostream>
#include <sys/mman.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	const char* shm_name = "/my_shm";
	int shd = shm_open(shm_name, O_RDWR, 0666);
	if(shd == -1)
	{
		perror("Cant shmopen");
		exit(errno);
	}

	if(unlink(shm_name) == -1)
	{
		perror("Cant unlink");
		exit(errno);
	}

	close(shd);
	return 0;
}
