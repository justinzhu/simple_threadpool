#ifndef __WORK_THREAD__
#define __WORK_THREAD__

#include <queue>

#include "thread.h"
#include "task.h"
#include "mutex.h"
#include "cond.h"

class ThreadManager;

class WorkThread : public Thread{
public:
	WorkThread( ThreadManager* );
	friend	class ThreadManager;
	virtual ~WorkThread();
	virtual void Run();
	void Stop();

private:
	void AddTask( Task* task );
	bool IsBusy();
	
private:
	ThreadManager * mThreadManager;
	bool mIsBusy;
	bool mQuit;
	Mutex mMutex;
	Cond mCond;
	std::queue<Task*> mTaskQueue;
} ;

#endif
