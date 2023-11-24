#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <sys/wait.h>

int main()
{
	int pipe_FD1[2];
	int pipe_FD2[2];
	if(pipe(pipe_FD1) == -1)
	{
		perror("Cant pipe");
		exit(errno);
	}
	if(pipe(pipe_FD2) == -1)
        {
                perror("Cant pipe");
                exit(errno);
        }

	pid_t pid1 = fork();
	if(pid1 == -1)
	{
                perror("Cant fork1");
                exit(errno);
	}
	if(pid1 == 0)
	{
		pid_t curpid = getpid();
		std::cout << "Helo ara " << curpid << std::endl;
		if(write(pipe_FD1[1], &curpid, sizeof(pid_t)) == -1)
		{
			perror("Cant write");
                	exit(errno);
		}
		if(read(pipe_FD2[0], &curpid, sizeof(pid_t)) == -1)
		{
			perror("Cant read");
                	exit(errno);
		}
		std::cout << "Helo ara " << curpid << std::endl;
		exit;
	}
	else{
		pid_t pid2 = fork();
		if(pid2 == -1)
		{
			perror("Cant fork2");
                	exit(errno);
		}
		if(pid2 == 0)
		{
			pid_t curpid = getpid();
			std::cout << "Aran du es " << curpid << std::endl;
			if(write(pipe_FD2[1], &curpid, sizeof(pid_t)) == -1)
                	{
                        	perror("Cant write");
                        	exit(errno);
                	}
                	if(read(pipe_FD1[0], &curpid, sizeof(pid_t)) == -1)
                	{	
                        	perror("Cant read");
                        	exit(errno);
                	}
			std::cout << "Aran du es " << curpid << std::endl;
		}
		waitpid(pid2, nullptr, 0);
	}
	waitpid(pid1, nullptr, 0);
	return 0;
}	
