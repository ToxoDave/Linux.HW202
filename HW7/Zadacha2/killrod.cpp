#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <signal.h>
#include <sys/wait.h>

int main()
{
	pid_t fk = fork();
	if(fk == -1)
	{
		perror("Cant fork");
		exit(errno);
	}
	if(fk == 0)
	{
		int id = getppid();
		if(kill(id, SIGKILL) < 0)
		{
			perror("Cant kill");
			exit(errno);
		}
		else {
			std::cout << "Parent killed x_x" << std::endl;
		}
	}



	return 0;
}
