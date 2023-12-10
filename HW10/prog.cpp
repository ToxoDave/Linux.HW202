#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>

struct Thread{
	int x;
	int y;
	std::string operand;
	const char* os_res;
};

void* foo(void* arg)
{
	int res = 0;
	Thread* tmp = (Thread*)arg;
	if(tmp->operand == "s")
	{
		res = tmp->x + tmp->y;
	}
	if(tmp->operand == "m")
	{
		res = tmp->x * tmp->y;
	}
	if(tmp->operand == "ss")
	{
		res = tmp->x * tmp->x + tmp->y * tmp->y;
	}
	
	int fd = open(tmp->os_res, O_WRONLY | O_RDONLY | O_CREAT, 0666);
	if(fd == -1)
	{
		perror("Cant open");
		exit(errno);
	}

	std::string res_str = std::to_string(res);
	ssize_t written_bytes = write(fd, res_str.c_str(), res_str.size());
	if(written_bytes == -1)
	{
		perror("Cant write");
		exit(errno);
	}
	close(fd);
	return nullptr;
}

int main()
{
	int N;
	std::cout << "Enter the number of operations :";
	std::cin >> N;
	std::cout << std::endl;
	std::vector<pthread_t> threads;
	std::vector<Thread> data;
	for(int i = 1; i <= N; ++i)
	{
		std::cin >> (data[i]).x >> (data[i]).y >> (data[i]).operand;
		std::string out = "out_" + std::to_string(i);
		data[i].os_res = out.c_str();
		if(pthread_create(&threads[i], nullptr, foo, (void*)&data[i]) == -1)
		{
			perror("Cant create thread");
			exit(errno);
		}
	}
	for(int j = 1; j <= N; ++j)
	{
		pthread_join(threads[j], nullptr);
	}	
	return 0;
}
