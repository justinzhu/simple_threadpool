#ifndef __COND_H__
#define __COND_H__

#include <pthread.h>

class Cond{
public:
	Cond();
	~Cond();
	bool Wait( pthread_mutex_t* );
	bool Notify();
	bool NotifyAll();
private:
	pthread_cond_t mCond;
};

#endif
