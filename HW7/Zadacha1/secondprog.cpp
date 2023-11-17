#include <iostream>
#include <sys/types.h>
#include <signal.h>

int count = 0;

void SignalHandler(int signum)
{
	if(signum == SIGINT)
	{
		std::cout << "The count of signals now: " << count << std::endl;
		exit(0);	
	}
	if(signum == SIGUSR2)
	{
		++count;
		return;
	}
}

int main()
{
	std::cout << "Take my PID: " << getpid() << std::endl;
	struct sigaction act1 = {};
	act1.sa_handler = SignalHandler;
	if(sigaction(SIGUSR2, &act1, nullptr) == -1)
	{
		perror("Error SIGUSR2");
		exit(errno);
	}
	struct sigaction act2 = {};
        act2.sa_handler = SignalHandler;
        if(sigaction(SIGINT, &act2, nullptr) == -1)
        {
                perror("Error SIGINT");
                exit(errno);
        }
	struct sigaction act3 = {};
        act3.sa_handler = SIG_IGN;
        if(sigaction(SIGUSR1, &act3, nullptr) == -1)
        {
                perror("Error SIGUSR1");
                exit(errno);
        }

	while(true)
	{
		std::cout << "AH, HA, HA, HA, STAYIN ALIVE, STAYIN ALIVE... " << std::endl;
		sleep(5);
	}
	return 0;
}
