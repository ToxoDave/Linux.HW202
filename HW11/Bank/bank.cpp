#include <iostream>
#include <vector>
#include <pthread.h>

class BankAccount{
	private:
		pthread_mutex_t* mutex;
	public:
		int balance = 0;

		BankAccount()
		{
			mutex = new pthread_mutex_t();
			pthread_mutex_init(mutex, nullptr);
		}
		~BankAccount()
		{
			pthread_mutex_destroy(mutex);
			delete mutex;
		}
		void debit(int amount)
		{
			pthread_mutex_lock(mutex);
			balance -= amount;
			pthread_mutex_unlock(mutex);
		}
		void credit(int amount)
		{
			pthread_mutex_lock(mutex);
			balance += amount;
			pthread_mutex_unlock(mutex);
		}
};

BankAccount acc;

void* plus(void* arg)
{
	int tmp = *((int*)arg);
	acc.credit(tmp);
	return nullptr;
}
void* minus(void* arg)
{
	int tmp = *((int*)arg);
        acc.debit(tmp);
	return nullptr;
}

int main()
{
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
		if(symb == '-')
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
