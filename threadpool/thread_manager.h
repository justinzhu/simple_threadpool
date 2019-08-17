#ifndef __THREAD_MANAGER_H__
#define __THREAD_MANAGER_H__

#include <list>
#include <pthread.h>
#include <stdint.h>

#include "task.h"
#include "mutex.h"
#include "work_thread.h"


class ThreadManager{
public:
	ThreadManager(uint32_t poolSize);
	~ThreadManager();
	bool Start();
	bool Stop();
	void AddTask( Task* task );
	void OnIdle( pthread_t );

private:
	uint32_t mPoolSize;
	Mutex mMutex;
	std::list<WorkThread*> mThreadPool; 
	std::list<WorkThread*> mDeadThreads;
};


#endif
