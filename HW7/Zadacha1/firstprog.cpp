#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <cerrno>
#include <string>

void SignalHandler(int sig)
{
	
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		perror("ERROR\n");
		exit(errno);
	}
	
	struct sigaction act = {};
	act.sa_handler = SignalHandler;

	int signum = std::stoi(argv[1]);
	int id = std::stoi(argv[2]);

	if(kill(id, signum) == -1)
	{
		perror("Cant send");
		exit(errno);
	}
}
