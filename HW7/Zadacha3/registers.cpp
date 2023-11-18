#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cerrno>
#include <cstdlib>
#include <sys/types.h>

void SignalHandler(int signum)
{
	std::cout << getpid() << std::endl;
	
	unsigned long eip_stat, eax_stat, ebx_stat;
	asm("movq %%rip, %0" : "=r" (eip_stat));
   	asm("movq %%rax, %0" : "=r" (eax_stat));
    	asm("movq %%rbx, %0" : "=r" (ebx_stat));

    	std::cout << "EIP: " << eip_stat << std::endl;
    	std::cout << "EAX: " << eax_stat << std::endl;
    	std::cout << "EBX: " << ebx_stat << std::endl;
}

int main()
{
	std::cout << "Now running process with PID: " << getpid();

	struct sigaction act = {};
	act.sa_handler = SignalHandler;

	if(sigaction(SIGUSR1, &act, nullptr) == -1)
	{
		perror("Error sendin signal");
		exit(errno);
	}

	while(true)
	{
		sleep(10);
	}
	return 0;
}
