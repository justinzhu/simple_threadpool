#include "thread_manager.h"

#include <iostream>

ThreadManager::ThreadManager( uint32_t poolSize )
:mPoolSize(poolSize) {

}

ThreadManager::~ThreadManager(){
	if ( mThreadPool.empty() )
		return;

	for( std::list<WorkThread*>::iterator it=mThreadPool.begin(); it!=mThreadPool.end(); ++it ){
		delete *it;
	}
}

bool ThreadManager::Start( ){
	ScopeLock guard(mMutex);
	for( uint32_t i=0; i<mPoolSize; i++ ){
		WorkThread* t = new WorkThread( this );
		t->Start();
		mThreadPool.push_back( t );
	}
}

bool ThreadManager::Stop(){
	ScopeLock guard(mMutex);
	for( std::list<WorkThread*>::iterator it=mThreadPool.begin(); it!=mThreadPool.end(); ++it ){
		(*it)->Stop();
	}	
}

void ThreadManager::AddTask( Task* task ){
	ScopeLock guard(mMutex);
	for ( std::list<WorkThread*>::iterator it=mThreadPool.begin(); it!=mThreadPool.end(); ++it ){
		if ( !(*it)->IsBusy() ){
			(*it)->AddTask( task );
			return;
		}
	}	
		
	WorkThread* t = new WorkThread( this );
	t->Start();
	mThreadPool.push_back( t );
	t->AddTask( task );
}

void ThreadManager::OnIdle( pthread_t id ){
	ScopeLock guard(mMutex);
	for ( std::list<WorkThread*>::iterator it = mDeadThreads.begin(); it != mDeadThreads.end(); ++it ){
		(*it)->Stop();
		delete *it;
	}
	mDeadThreads.clear();

	if ( mPoolSize >= mThreadPool.size() ){
		return;	
	}

	for ( std::list<WorkThread*>::iterator it=mThreadPool.begin(); it!=mThreadPool.end();  ){
		if( id == (*it)->GetId() ){
			mDeadThreads.push_back(*it);
			it = mThreadPool.erase(it);
		}	
		else
			++it;
	}
}

