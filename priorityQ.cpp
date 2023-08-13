// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 6 mario kart
//  implement a binary min heap to use a 
//   priority q that will simulate racers getting
//   closer to a finish line 
#include "priorityQ.h"
#include <cstdlib>
using namespace std;

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() 
{
	size = 1; 
	capacity = 5;
	heapArray = new priorityType[capacity];
}

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2>& copy) 
{
	//deep copy 
	size = copy.size;
	capacity = copy.capacity;
	heapArray = new priorityType[capacity];
	for(int i = 0; i < capacity; i++)
		heapArray[i] = copy.heapArray[i];
	itemToPQ = copy.itemToPQ;
}

template <class t1, class t2>
const priorityQ<t1, t2>& priorityQ<t1, t2>::operator=(const priorityQ<t1, t2>& rhs)
{
	//deep copy 
    if (this != &rhs)
    {
		delete[] heapArray;
		size = rhs.size;
		capacity = rhs.capacity;
		heapArray = new priorityType[capacity];
		for(int i = 0; i < capacity; i++)
			heapArray[i] = rhs.heapArray[i];
		itemToPQ = rhs.itemToPQ;
    }

    return *this;
}

template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
	size = 0;
	capacity = 0;
	delete[] heapArray;
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
	if(size == capacity)
	{
		//resize 
		priorityType * temp = heapArray;
		capacity = capacity*2;
		heapArray = new priorityType[capacity];
		for(int i = 0; i < capacity/2; i++)
			heapArray[i] = temp[i];
		delete [] temp;
	}
	priorityType element{key, priority};
	heapArray[size++] = element;
	itemToPQ[key] = size-1;
	bubbleUp(size-1); 
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
	//assign the last element of heapArray to root 
	heapArray[1].key = heapArray[size-1].key;
	heapArray[1].priority = heapArray[size-1].priority;
	size--;
	//update itemToPQ accordingly 
	itemToPQ[heapArray[1].key] = 1;
	//bubble down 
	bubbleDown(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1& key, const t2& priority)
{
	//bubble up after DECREASING 
	size_t index = itemToPQ[key];
	heapArray[index].priority = priority;
	bubbleUp(index);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
	return heapArray[1].priority; 
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
	return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
	if(size <= 1)
		return true;
	else 
		return false;
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
	 // nothing to bubble up (we are done)
	if(index == 0 || index == 1)
		return;
	//get parent index
	size_t parentIndex; 
	parentIndex = index/2;
	//if priority in parent is greater than 
	// priority in index we swap and bubble up on parent index 
	priorityType parent = heapArray[parentIndex];
	priorityType curr = heapArray[index];
	if(parent.priority > curr.priority)
	{
		//swap
		heapArray[index].key = parent.key;
		heapArray[index].priority = parent.priority;
		heapArray[parentIndex].key = curr.key;
		heapArray[parentIndex].priority = curr.priority;
		itemToPQ[curr.key] = parentIndex;
		itemToPQ[parent.key] = index; 
		bubbleUp(parentIndex);
	}
	
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    size_t leftChildIndex = index*2;
	size_t rightChildIndex = leftChildIndex+1;
	//check if we have a left child 
	if(leftChildIndex > size)
		return;
	priorityType leftChild = heapArray[leftChildIndex];
	priorityType curr = heapArray[index];
	priorityType min;
	size_t minIndex; 
	if(rightChildIndex <= size) // in the case we have a right child also
	{
		priorityType rightChild = heapArray[rightChildIndex];
		if(rightChild.priority < leftChild.priority && rightChild.priority < curr.priority)
			//set min to right child
			{min = rightChild;minIndex = rightChildIndex;}
		else if(leftChild.priority < curr.priority)
			//set min to leftChild
			{min = leftChild;minIndex = leftChildIndex;}
	}
	else if(leftChild.priority < curr.priority) // in the case only a left child exist 
		//set min to leftChild
		{min = leftChild;minIndex = leftChildIndex;}
	
	if(min.key != t1()) // a min exists 
	{
		//swap min with current
		heapArray[index].key = min.key;
		heapArray[index].priority = min.priority;
		heapArray[minIndex].key = curr.key;
		heapArray[minIndex].priority = curr.priority;
		itemToPQ[curr.key] = minIndex;
		itemToPQ[min.key] = index; 
		//bubble down
		bubbleDown(minIndex);
	}
	else 
		return;
}