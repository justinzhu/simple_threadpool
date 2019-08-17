#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread{
public:
	Thread( );
	virtual ~Thread();
	bool Start();
	static void* ThreadFunc( void* );
	virtual void Run() = 0; 
	pthread_t GetId() { return mTid; }
private:
	pthread_t mTid;
	pthread_attr_t  attr;
};


#endif
