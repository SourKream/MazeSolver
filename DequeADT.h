#ifndef DEQUEADT_H
#define DEQUEADT_H

/**
 * Interface Deque represents an abstract data type (ADT) for a double-ended queue.
 * A deque allows efficient insertion and removal at its front and back, combining
 * many of the benefits of stacks and queues into a single collection.
 * 
 * Classes implementing Deque are generally expected to provide the operations
 * below in O(1) constant amortized runtime, except for the toString and clear
 * operations.
 */

template <class value_type>
class DequeADT {

	public :
		virtual void push_front (const value_type& val) = 0;
		virtual void push_back (const value_type& val) = 0;
		virtual void clear() = 0;
		virtual bool empty() = 0;
		virtual value_type front() = 0;
		virtual value_type back() = 0;
		virtual value_type at(int index) = 0;
		virtual void pop_front() = 0;
		virtual void pop_back() = 0;
		virtual int size() = 0;
};

#endif
