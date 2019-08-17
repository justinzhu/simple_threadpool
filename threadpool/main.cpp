#include <iostream>
#include <unistd.h>

#include "thread.h"
#include "work_thread.h"
#include "thread_manager.h"
#include "task.h"

class TaskA : public Task{
public:
	virtual void Execute(){
		std::cout <<"TaskA" << std::endl;
		sleep(1);
	}
};
class TaskB : public Task{
public:
	virtual void Execute(){
		std::cout <<"TaskB" << std::endl;
		sleep(1);
	}
};


int main(){
	ThreadManager* tm = new ThreadManager(10) ;
	
	tm->Start();

	for(int i=0; i<20; i++ ){
		if(i%2==0)
			tm->AddTask( new TaskA );
		else
			tm->AddTask( new TaskB );
	}
	sleep(5);
	tm->Stop();	

	return 0;
}
