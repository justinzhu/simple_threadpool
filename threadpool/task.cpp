#include "task.h"

void Task::Run(){
	Execute();
	delete this;
}
