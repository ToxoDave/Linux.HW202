#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>

class Number {
public:
	int x = 0;
};

pthread_mutex_t* mutex = new pthread_mutex_t();
pthread_spinlock_t* spinlock = new pthread_spinlock_t();
sem_t* semaphore = new sem_t();

void* example_mutex(void* arg) {
        Number* num = (Number*)arg;
        for(int i = 0; i < 10000; ++i)
        {
		pthread_mutex_lock(mutex);
                num->x++;
		pthread_mutex_unlock(mutex);
        }
        return nullptr;
}

void* example_spinlock(void* arg) {
        Number* num = (Number*)arg;
        for(int i = 0; i < 10000; ++i)
        {
		pthread_spin_lock(spinlock);
                num->x++;
		pthread_spin_unlock(spinlock);
        }
        return nullptr;
}


void* example_semaphore(void* arg) {
  	Number* num = (Number*)arg;
  	for(int i = 0; i < 10000; ++i) 
	{
		sem_wait(semaphore);
    		num->x++;
		sem_post(semaphore);
  	}
  	return nullptr;
}

int main(int argc, char** argv) {
  	Number* num = new Number();
  	num->x = 2;
  	std::vector<pthread_t> tids(20);
	clock_t start_time, end_time;
	pthread_mutex_init(mutex, nullptr);
	pthread_spin_init(spinlock, 0);
	sem_init(semaphore, 0, 1);

	//for mutex
/*	start_time = clock();
  	for(int i = 0; i < 20; ++i)
       	{
    		pthread_create(&tids[i], NULL, example_mutex, (void*)num);  
  	}
	
 	for(int i = 0; i < 20; ++i) 
 	{
    		pthread_join(tids[i], NULL);
  	}
	end_time = clock();
	std::cout << "This is runtime for mutex :" << end_time - start_time << std::endl;
*/	
/*	//for spinlock
	num->x = 2;
	start_time = clock();
        for(int i = 0; i < 20; ++i)
        {
                pthread_create(&tids[i], NULL, example_spinlock, (void*)num);
        }

        for(int i = 0; i < 20; ++i)
        {
                pthread_join(tids[i], NULL);
        }
        end_time = clock();
        std::cout << "This is runtime for spinlock :" << end_time - start_time << std::endl;
*/
	//for semaphore
	num->x = 2;
	start_time = clock();
        for(int i = 0; i < 20; ++i)
        {
                pthread_create(&tids[i], NULL, example_semaphore, (void*)num);
        }

        for(int i = 0; i < 20; ++i)
        {
                pthread_join(tids[i], NULL);
        }
        end_time = clock();
        std::cout << "This is runtime for semaphore :" << end_time - start_time << std::endl;

	pthread_mutex_destroy(mutex);
	pthread_spin_destroy(spinlock);
	sem_destroy(semaphore);


  std::cout << num->x << std::endl;
  delete num;

  return 0;
}
