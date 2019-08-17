#include "thread.h"

#include <iostream>
#include <unistd.h>

#include "task.h"

Thread::Thread( )
	:mTid(0){
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
}

Thread::~Thread(){

}

bool Thread::Start(){
	return 0==pthread_create( &mTid, &attr, &Thread::ThreadFunc, (void*)this );
}

void* Thread::ThreadFunc( void* arg ){
	Thread* self = (Thread*)arg; 
	self->Run();
	return NULL;
}


