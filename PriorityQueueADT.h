#ifndef PRIORITYQUEUEADT_H
#define PRIORITYQUEUEADT_H

#include "Point.h"

class PriorityQueueADT {
	
	public :

		virtual void push (const Point& val) = 0;
		virtual bool empty() = 0;
		virtual Point top() = 0;
		virtual void pop() = 0;
		virtual int size() = 0;
};

#endif
