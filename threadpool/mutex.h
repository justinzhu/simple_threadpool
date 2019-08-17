#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

class Mutex{
public:
	Mutex();
	~Mutex();
	bool Lock();
	bool Unlock();
	pthread_mutex_t* Get();
private:
	pthread_mutex_t mMutex;
};

class ScopeLock{
public:
	ScopeLock( Mutex& mutex );
	~ScopeLock( );
private:
	Mutex& mMutex;
};
#endif
