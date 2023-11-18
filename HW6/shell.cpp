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
		int i = 0;
		while(token != nullptr && strcmp(token, "&&") != 0 && strcmp(token, "||") != 0)
		{
			tokens.push_back(token);
			token = strtok(nullptr, " ");
			++i;
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
				for(int k = i; k < s.size(); ++k)
       		 		{
                			if(tokens[k] == "&&")
                			{
						int j = k + 1;
                				std::vector<char*> new_tokens;
						while(tokens[j] != "&&" && tokens[j] != "||")
						{
                					new_tokens.push_back(tokens[j]);
							++j;
						}
						k = j;
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
						while(!new_tokens.empty())
						{
                					new_tokens.pop_back();
						}
					}
					else if(tokens[k] == "||")
					{
						return 0;
					}
                    		}
			}
			else{
			     for(int k = i; k < s.size(); ++k)
                             {
				if(tokens[k] == "||")
				{
					int j = k + 1;
	     				std::vector<char*> new_tokens;
					while(tokens[j] != "||" && tokens[j] != "&&")
					{
						new_tokens.push_back(tokens[j]);
						++j;
					}
					k = j;
					pid_t fk = fork();
					if(fk == -1)
					{
						perror("Cant fork");
						exit(EXIT_FAILURE);
					}
					if(fk == 0)
					{
						if(execvp(new_tokens[0], new_tokens.data())== -1)
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
					while(!new_tokens.empty())
					{
						new_tokens.pop_back();
					}
				}
			     }
			}
	} // while
	return 0;
}
