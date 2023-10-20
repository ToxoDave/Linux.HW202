#include <iostream>
#include <errno.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		std::cout << "You cant use this command";
		return 8;
	}
	const char *filename = argv[1];
	int id = open(filename, O_RDONLY);

	if(id == -1)
	{
		perror("Cant open file");
		return 8;
	}

	char buffer[4096];
	ssize_t read_bytes;

	while((read_bytes = read(id, buffer, 4096)) != 0)  
	{
	        if(read_bytes < -1)
	        {
			perror("Cant write");
			return 8;
	        }
		write(1, buffer, read_bytes);		
	}
	close(id);

	return 0;
}
