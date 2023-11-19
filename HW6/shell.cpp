#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>

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
		for(int p = 1; p < i; ++p)
		{
			if(strcmp(tokens[p], ">") == 0)
			{
				ssize_t buf_size = 4096;
				char buffer[buf_size];
				std::vector<char*> new_tokens;
				int y = 0;
				while(y < p) {
					new_tokens.push_back(tokens[y]);
					++y;
				}
				if(p - y > 1)
				{
					int read_bytes = 0;
					int fd = open(tokens[y + 1], O_WRONLY);
					if(fd == -1)
					{
						perror("cant open");
						exit(errno);
					}
					int b = 0;
					while(b < y)
					{
						int fd2 = open(new_tokens[b], O_RDONLY);
						while((read_bytes = read(fd2, buffer, 1) > 0))
						{
							if(write(fd, buffer, 1) == -1)
							{
								perror("Cant write");
								exit(errno);
							}
						}
						close(fd2);
						++b;
					}
				}
			}
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
					char* curtok = tokens[k];
                			if((strcmp(curtok, "&&") == 0))
                			{
						int j = k + 1;
                				std::vector<char*> new_tokens;
						while((strcmp(tokens[j], "&&") != 0) && (strcmp(tokens[j], "||") != 0))
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
						if(WEXITSTATUS(status) != 0)
						{
							std::cout << "No more ececutes";
							return 0;
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
				char* curtok = tokens[k];
				if((strcmp(tokens[k],  "||") == 0))
				{
					int j = k + 1;
	     				std::vector<char*> new_tokens;
					while((strcmp(tokens[j], "&&") != 0) && (strcmp(tokens[j], "||") != 0))
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
					if(WEXITSTATUS(status) == 0)
					{
						return 0;
					}
				}
			     }
			}
	} // while
	return 0;
}
