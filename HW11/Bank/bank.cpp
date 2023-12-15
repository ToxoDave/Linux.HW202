#include <iostream>
#include <vector>
#include <pthread.h>

pthread_mutex_t* global_mutex;

class BankAccount{
	public:
		int balance = 0;

		void debit(int amount)
		{
			balance -= amount;
		}
		void credit(int amount)
		{
			balance += amount;
		}
};

BankAccount acc;

void* plus(void* arg)
{
	int tmp = *((int*)arg);
	pthread_mutex_lock(global_mutex);
	acc.credit(tmp);
	pthread_mutex_unlock(global_mutex);
	return nullptr;
}
void* minus(void* arg)
{
	int tmp = *((int*)arg);
	pthread_mutex_lock(global_mutex);
        acc.debit(tmp);
        pthread_mutex_unlock(global_mutex);
	return nullptr;
}

int main()
{
	global_mutex = new pthread_mutex_t();
	int N;
	std::cin >> N;
	std::vector<pthread_t> threads(N);

	char symb;
	int num;
	for(int i = 0; i < N; ++i)
	{
		std::cin >> symb >> num;
		if(symb == '+')
		{
			if(pthread_create(&threads[i], nullptr, plus, &num) != 0)
                	{
                        	std::cerr << "Cant create credit" << std::endl;
                        	exit(EXIT_FAILURE);
                	}
		}
		else if(symb == '-')
		{
			if(pthread_create(&threads[i], nullptr, minus, &num) != 0)
			{
				std::cerr << "Cant create debit" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	for(int i = 0; i < N; ++i)
	{
		pthread_join(threads[i], nullptr);
	}
	std::cout << "Your account balance right now is : " << acc.balance << "$" << std::endl;
	return 0;
}


