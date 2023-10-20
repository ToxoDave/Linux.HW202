#include <iostream>
#include <string>
#include <fcntl.h>
#include <cerrno>
#include <vector>
#include <unistd.h>

int main(int argc, char** argv)
{
	std::cout << "Enter the name of the source file:" << std::endl;
	char* source;
	std::cin >> source;
	std::cout << "Enter the name of the destination file:" << std::endl;
	char* destination;
	std::cin >> destination;
	std::cout << "Enter the initial offset in the source file(in bytes):" << std::endl;
	ssize_t source_bytes;
	std::cin >> source_bytes;
	std::cout << "Enter the initial offset in the destination file (in bytes):" << std::endl;
	ssize_t destination_bytes;
	std::cin >> destination_bytes;
	std::cout << "Enter the number of bytes to copy:" << std::endl;
	ssize_t copy_bytes;
	std::cin >> copy_bytes;

	int sf = open(source, O_RDONLY, 0666);
	int fd = open(destination, O_WRONLY | O_RDONLY | O_TRUNC, 0666);

	if(sf == -1 || fd == -1)
	{
		perror("Cant open");
		exit(EXIT_FAILURE);
	}

	int ls1 = lseek(sf, source_bytes, SEEK_SET);
	int ls2 = lseek(fd, destination_bytes, SEEK_SET);

	if(ls1 == -1 || ls2 == -1)
	{
		perror("Cant lseek");
		exit(EXIT_FAILURE);
	}
	
	int buff_size = 4096;
	char buffer[buff_size];
	for(ssize_t i = 0; i <= copy_bytes; )
	{
		int bytes_read = read(sf, buffer, buff_size);
		if(bytes_read == -1)
		{
			perror("Cant read");
			exit(EXIT_FAILURE);
		}
		int bytes_written = write(fd, buffer, bytes_read);
		if(bytes_written == -1)
		{
			perror("Cant write");
			exit(EXIT_FAILURE);
		}
		i += bytes_read;
	}
	close(sf);
	close(fd);
}
