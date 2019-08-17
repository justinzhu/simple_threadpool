#include "work_thread.h"

#include <iostream>
#include <stdexcept>

#include "thread_manager.h"


WorkThread::WorkThread( ThreadManager* tm )
:mThreadManager(tm)
,mIsBusy(false)
,mQuit(false){

}

WorkThread::~WorkThread(){

}

void WorkThread::Run(){
	while(true){
		Task* task = NULL;

		{
			ScopeLock guard(mMutex);
			if( mTaskQueue.empty() ){
				if( mQuit )
					break;
				else{
					mCond.Wait( mMutex.Get() );
					continue;
				}
			}

			task = mTaskQueue.front();
			mTaskQueue.pop();
		}	
		
		try{
			task->Run();
		}catch( std::exception& e){
			std::cout <<"exception: "<< e.what() << std::endl;
		}	

		{
			ScopeLock guard(mMutex);
			mIsBusy = false;
			mThreadManager->OnIdle( GetId() );
		}
	}
}


void WorkThread::Stop(){
	ScopeLock guard(mMutex);
	mQuit = true;
	if ( !mIsBusy )
		mCond.Notify();

}

void WorkThread::AddTask( Task* task ){
	ScopeLock guard(mMutex);
	mTaskQueue.push( task );
	if ( mTaskQueue.size()==1 ){
		mIsBusy = true;
		mCond.Notify();
	}
}

bool WorkThread::IsBusy(){
	bool running =false;
	{
		ScopeLock guard(mMutex);
		running = mIsBusy;
	}
	return running;
}
