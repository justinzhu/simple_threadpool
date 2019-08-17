#include "cond.h"

Cond::Cond(){
	pthread_cond_init( &mCond, NULL );
}

Cond::~Cond(){
	pthread_cond_destroy( &mCond );
}

bool Cond::Wait( pthread_mutex_t* mutex ){
	return 0 == pthread_cond_wait( &mCond, mutex );
}

bool Cond::Notify(){
	return 0 == pthread_cond_signal( &mCond );
}

bool Cond::NotifyAll(){
	return 0 == pthread_cond_broadcast( &mCond );
}
