#include "PriorityQueueADT.h"
#include "comparator.h"
#include "Point.h"

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class PriorityQueueSTL : public PriorityQueueADT {
	private:
		std::priority_queue<Point, vector<Point>, mycomparison> * pq;

	public:
		PriorityQueueSTL(Point *destination);

		void push (const Point& val);
		bool empty();
		Point top();
		void pop();
		int size();

};

PriorityQueueSTL::PriorityQueueSTL(Point *destination)
{
	pq = new priority_queue<Point, std::vector<Point>, mycomparison>(mycomparison(destination));
}


void PriorityQueueSTL::push (const Point& val)
{
	pq->push(val);
}
	
bool PriorityQueueSTL::empty()
{
	return pq->empty();
}
	
Point PriorityQueueSTL::top()
{
	return pq->top();
}
	
void PriorityQueueSTL::pop()
{
	pq->pop();
}
	
int PriorityQueueSTL::size()
{
	return pq->size();
}