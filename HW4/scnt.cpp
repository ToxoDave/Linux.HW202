#include <iostream>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <cerrno>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Error\n";
		exit(EXIT_FAILURE);
	}
	ssize_t fd  = open(argv[1], O_RDONLY, 0666);
	if(fd == -1)
	{
		perror("Cant open");
		exit(EXIT_FAILURE);
	}
	ssize_t buff_size = 4096;
	char buff[buff_size]; 
	int count = 0;
	ssize_t read_bytes;
	while((read_bytes = read(fd, buff, buff_size)) > 0)
	{
		if(read_bytes == -1)
		{
			perror("Cant read");
			exit(EXIT_FAILURE);
		}
		for(int i = 0; i < read_bytes; ++i)
		{
			if(buff[i] == '\n')
			{
				++count;
			}
		}
	}
	std::cout << "The number of lines is: "  << count << "\n";

	ssize_t op = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(op == -1)
	{
		perror("Cant open");
	       	exit(EXIT_FAILURE);
	}

	off_t ls = lseek(fd, 0, SEEK_END);
	if(ls == -1)
	{
		perror("Cant lseek");
		exit(EXIT_FAILURE);
	}
	char buff_for_reverse[buff_size];

	for(off_t i = ls - 2; i >= 0; --i)
	{
		ssize_t shf = lseek(fd, i, SEEK_SET);
		if(shf == -1)
		{
			perror("Cant lseek");
			exit(EXIT_FAILURE);
		}
		ssize_t rd = read(fd, buff_for_reverse, 1);
		if(rd == -1)
		{
			perror("Cant read");
			exit(EXIT_FAILURE);
		}
		ssize_t wr = write(op, buff_for_reverse, 1);
		if(wr == -1)
		{
			perror("Cant write");
			exit(EXIT_FAILURE);
		}
	}

	close(fd);
	return 0;
}
