#ifndef __ABSTRACT_TASK__
#define __ABSTRACT_TASK__


class Task {
public:
	virtual void Execute() = 0;
	void Run();

};


#endif
