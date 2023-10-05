#include <iostream>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cout << "You cant use this command";
		return 8;
	}
	const char* filename1 = argv[1];
	const char* filename2 = argv[2];

	int id1 = open(filename1, O_RDONLY);
	int id2 = open(filename2, O_TRUNC | O_CREAT | O_WRONLY);

	if(id1 == -1 || id2 == -1)
	{
		perror("Cant open file");
		return 8;
	}
	
	char buffer[1];
	ssize_t read_bytes;

	while((read_bytes = read(id1, buffer, 1)) != 0)
	{
		if(read_bytes == -1)
		{
			perror("Cant read");
			return 8;
		}
		ssize_t write_bytes = write(id2, buffer, 1);
		if(write_bytes == -1)
		{
			perror("Cant write");
			return 8;
		}
	}

	close(id1);
	close(id2);    

	return 0;
	
}
