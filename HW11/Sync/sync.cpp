#include <iostream>
#include <vector>
#include <pthread.h>

class Number {
public:
	int x = 0;
};

void* example(void* arg) {
  	Number* num = (Number*)arg;
  	for(int i = 0; i < 10000; ++i) 
	{
    		num->x++;
  	}
  	return nullptr;
}

int main(int argc, char** argv) {
  	Number* num = new Number();
  	num->x = 2;
  	std::vector<pthread_t> tids(20);

  	for(int i = 0; i < 20; ++i)
       	{
    		pthread_create(&tids[i], NULL, example, (void*)num);  
  	}
	
  for(int i = 0; i < 20; ++i) 
  {
    	pthread_join(tids[i], NULL);
  }

  std::cout << num->x << std::endl;
  delete num;

  return 0;
}
