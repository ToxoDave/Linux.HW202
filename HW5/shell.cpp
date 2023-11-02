#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

int main(int argc, char** argv)
{
	while(true)
	{
		std::cout<< "MyShell> ";
		std::string s;
		std::getline(std::cin, s);
		if(s == "exit")
		{
			std::cout << "exit";
			break;
		}
		std::vector<char*> tokens;
		char* token = strtok(const_cast<char*>(s.c_str()), " ");
		while(token != nullptr)
		{
			tokens.push_back(token);
			token = strtok(nullptr, " ");
		}
		pid_t fk = fork();
		if(fk == -1)
		{
			perror("Cant fork");
			exit(EXIT_FAILURE);
		}
		int status;
		if(fk == 0)
		{
			if(execvp(tokens[0], tokens.data()) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if(wait(&status) == -1)
			{
				perror("Cant wait");
				exit(EXIT_FAILURE);
			}	
		}

		if(WIFEXITED(status))
		{
			std::cout << "exit code " << WEXITSTATUS(status) << std::endl;
		}
	}
	return 0;
}
