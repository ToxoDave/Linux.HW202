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
		int status;
		pid_t fk = fork();
                        if(fk == -1)
                        {
                                perror("Cant fork");
                                exit(EXIT_FAILURE);
                        }
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
			if(WEXITSTATUS(status) == 0)
			{
				for(int i = 1; i < s.size(); ++i)
       		 		{
                			if(tokens[i] == "&&")
                			{
                				std::vector<char*> new_tokens;
						int j = i + 1;
						while(tokens[j] != "&&")
						{
                					new_tokens.push_back(tokens[j]);
							++j;
						}
						i = j;
                        			pid_t fr = fork();
                        			if(fr == -1)
                        			{
                                			perror("Cant fork");
                                			exit(EXIT_FAILURE);
                        			}
                        			if(fr == 0)
                        			{
                                			if(execvp(new_tokens[0], new_tokens.data()) == -1)
                                			{
                                        			perror("Cant run");
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
                				new_tokens.pop_back();
					}
				}
			}
/*
                        if(WIFEXITED(status))
                        {
                                std::cout << "exit code " << WEXITSTATUS(status) << std::endl;
                        }



	for(int i = 1; i < s.size(); ++i)
	{
		if(tokens[i] == "&&")
		{
		std::vector<char*> new_tokens;
		new_tokens.push_back(tokens[i + 1]);
			pid_t fr = fork();
			if(fr == -1)
			{
				perror("Cant fork");
				exit(EXIT_FAILURE);
			}
			if(fr == 0)
			{

				if(execvp(new_tokens[0], new_tokens.data()) == -1)
				{
					perror("Cant run");
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
		new_tokens.pop_back();

			if(WIFEXITED(status))
                	{
				if(WEXITSTATUS(status) == 0)
				{
					new_tokens.push_back(tokens[i + 1]);
					pid_t fr2 = fork();
                               		if(fr2 == -1)
                                	{
                                       		perror("Cant fork 2");
                                        	exit(EXIT_FAILURE);
                                	}
                                	if(fr2 == 0)
                                	{
                                        	if(execvp(new_tokens[0], new_tokens.data()) == -1)
                                        	{
                                                	perror("Cant run 2");
                                                	exit(EXIT_FAILURE);
                                        	}
                                	}
					else{
						 if(wait(&status) == -1)
                                		 {
                                        		perror("Cant wait");
                                        		exit(EXIT_FAILURE);
                                		 }
					}
					if(WIFEXITED(status))
					{
						std::cout << "everything is okay \n";
					}	
				}	
                	}
		new_tokens.pop_back();
                } else {
			pid_t fk = fork();
			if(fk == -1)
			{
				perror("Cant fork");
				exit(EXIT_FAILURE);
			}
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
	} // for */
	} // while
	return 0;
}
