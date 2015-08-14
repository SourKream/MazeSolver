#include "PriorityQueueADT.h"
#include "comparator.h"
#include "Point.h"

#include <iostream>

using namespace std;

class PriorityQueueArray : public PriorityQueueADT {
	private:
        Point* Array;
        int Size, Capacity;              // Size stores number of elements in Array
        void increaseCapacity();         // Function to double the Capacity of Array
        void PercolateUp (int);
        void PercolateDown (int);
        mycomparison Compare;

	public:
		PriorityQueueArray(Point *destination);

		void push (const Point& val);
		bool empty();
		Point top();
		void pop();
		int size();

};

void PriorityQueueArray::increaseCapacity()
{
    Point* temp = new Point[2*Capacity];
    for(int i=0;i<Size;i++)
        temp[i] = Array[i];
    delete [] Array;
    Array = temp;
    Capacity*=2;
}

PriorityQueueArray::PriorityQueueArray(Point *destination) : Compare(destination)
{
    Capacity = 10;
    Array = new Point[Capacity];
    Size = 0;
}

void PriorityQueueArray::PercolateUp (int Index)
{
    while ((Index/2>0)&&(Compare(Array[Index/2],Array[Index])))
    {
        Point temp(Array[Index].getRow(),Array[Index].getColumn());
        Array[Index].setRow(Array[Index/2].getRow());
        Array[Index].setColumn(Array[Index/2].getColumn());
        Array[Index/2].setRow(temp.getRow());
        Array[Index/2].setColumn(temp.getColumn());
        Index/=2;
    }
}

void PriorityQueueArray::PercolateDown (int Index)
{
    if (2*Index>Size)
    {
        
    }
    else if (2*Index==Size)
    {
        if(Compare(Array[Index],Array[Index*2]))
        {
            Point temp(Array[Index].getRow(),Array[Index].getColumn());
            Array[Index].setRow(Array[Index*2].getRow());
            Array[Index].setColumn(Array[Index*2].getColumn());
            Array[Index*2].setRow(temp.getRow());
            Array[Index*2].setColumn(temp.getColumn());
        }
    }
    else
    {
        int n = 2*Index;
        if (Compare(Array[n],Array[n+1]))
            n++;
        if(Compare(Array[Index],Array[n]))
        {
            Point temp(Array[Index].getRow(),Array[Index].getColumn());
            Array[Index].setRow(Array[n].getRow());
            Array[Index].setColumn(Array[n].getColumn());
            Array[n].setRow(temp.getRow());
            Array[n].setColumn(temp.getColumn());
            PercolateDown(n);
        }
    }
}

void PriorityQueueArray::push (const Point& val)
{
    if(Size+1>Capacity-1)
        increaseCapacity();
    Size++;
    Array[Size] = val;
    PercolateUp(Size);
}
	
bool PriorityQueueArray::empty()
{
    if(Size==0)
        return true;
    else
        return false;
}

Point PriorityQueueArray::top()
{
    if(empty())
    {
        cout <<  "Queue is Empty";
        exit(0);
    }
    return Array[1];
}

void PriorityQueueArray::pop()
{
    if(empty())
    {
        cout <<  "Queue is Empty";
        exit(0);
    }
    Array[1].setRow(Array[Size].getRow());
    Array[1].setColumn(Array[Size].getColumn());
    Size--;
    PercolateDown(1);
}

int PriorityQueueArray::size()
{
    return Size;
}
