#include <iostream>
#include <string>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>

int main(int argc, char** argv)
{
	std::cout << "Enter the name of the source file:" << std::endl;
	std::string source;
	std::cin >> source;
	std::cout << "Enter the name of the destination file:" << std::endl;
	std::string destination;
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

	int sf = open(source.c_str(), O_RDONLY);
	int fd = open(destination.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);

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
	ssize_t bytes_read;
	char buffer[buff_size];
	while(copy_bytes > 0 && (bytes_read = read(sf, buffer, buff_size)) > 0)
	{
		int bytes_written = write(fd, buffer, bytes_read);
		if(bytes_written == -1)
		{
			perror("Cant write");
			exit(EXIT_FAILURE);
		}
		copy_bytes -= bytes_written;
	}
	close(sf);
	close(fd);



	return 0;
}
