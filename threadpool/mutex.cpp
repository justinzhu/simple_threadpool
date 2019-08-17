#include "mutex.h"

Mutex::Mutex(){
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&mMutex, &attr );
}

Mutex::~Mutex(){
	pthread_mutex_destroy(&mMutex);
}

bool Mutex::Lock(){
	return 0 == pthread_mutex_lock(&mMutex);
}

bool Mutex::Unlock(){
	return 0 == pthread_mutex_unlock(&mMutex);
}

pthread_mutex_t* Mutex::Get(){
	return &mMutex;
}

ScopeLock::ScopeLock( Mutex& mutex )
:mMutex(mutex){
	mMutex.Lock();
}

ScopeLock::~ScopeLock(){
	mMutex.Unlock();
}

