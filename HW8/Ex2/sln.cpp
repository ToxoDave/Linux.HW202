#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <string>
#include <cstring>

int main(int argc, char** argv)
{
	std::vector<std::string> vec1;
	std::vector<std::string> vec2;
	pid_t child1, child2;
	int i = 1;
	while((strcmp(argv[i], "?") != 0))
	{
		vec1.push_back(argv[i]);
	//	std::cout << "azaz: " << i << vec1[i] << std::endl;
		++i;
	}
	++i;
	while(argv[i] != nullptr)
	{
		vec2.push_back(argv[i]);
	//	std::cout << "azazazazaz: " << i << vec2[i] << std::endl;
		++i;
	}
	std::vector<char*> vec12(vec1.size() + 1);
	std::vector<char*> vec22(vec2.size() + 1);
	for(ssize_t j = 0; j < vec1.size(); ++j)
	{
		vec12[j] = const_cast<char*>(vec1[j].c_str());
	//	std::cout << j << " : " << vec12[j] << std::endl;
	}
	vec12[vec1.size()] = nullptr;
	for(ssize_t j = 0; j < vec2.size(); ++j)
        {
                vec22[j] = const_cast<char*>(vec2[j].c_str());
	//	std::cout << j << " : " << vec22[j] << std::endl;
	}
	vec22[vec2.size()] = nullptr;

	int pipe_FD[2];
	if(pipe(pipe_FD) == -1)
	{
		perror("Cant pipe");
		exit(errno);
	}
	child1 = fork();
	if(child1 == -1)
	{
                perror("Cant fork1");
                exit(errno);
	}
	if(child1 == 0)
	{
		std::cout << "Hi child 1";
		close(pipe_FD[0]);
		if(dup2(pipe_FD[1], 1) == -1)
		{
	                perror("Cant dup2");
                	exit(errno);
		}
		close(pipe_FD[1]);
	//	std::cout << "Child 1 is ready to execute" << std::endl;
		if(execvp(vec12[0], vec12.data()) == -1)
		{
	                perror("Cant execute 1");
        	        exit(errno);
		}
	}
	else{
		child2 = fork();
		if(child2 == -1)
		{
                	perror("Cant fork2");
                	exit(errno);
		}
		if(child2 == 0)
		{
			close(pipe_FD[1]);
			if(dup2(pipe_FD[0], 0) == -1)
			{
		                perror("Cant dup2");
		                exit(errno);
			}
			close(pipe_FD[0]);
	//		std::cout << "Child 2 is ready to execute" << std::endl;
			if(execvp(vec22[0], vec22.data()) == -1)
			{
			        perror("Cant execute 2");
				exit(errno);
			}
		}	
	}
	close(pipe_FD[0]);
	close(pipe_FD[1]);

	waitpid(child2, nullptr, 0);
	waitpid(child1, nullptr, 0);

	return 0;
}
