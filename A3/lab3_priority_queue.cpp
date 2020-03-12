#include "lab3_priority_queue.hpp"
#include <iostream>
using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) 
{
	//heap is an array of pointers which, each pointer points to a task item
	heap = new TaskItem*[n_capacity+1];
	capacity = n_capacity;
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() 
{
	for (int index = 0; index < size; index++){
		delete heap[index+1];
		heap [index+1] = NULL;
	}
	delete [] heap;
	heap = NULL;
	size = 0;
	capacity = 0;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (!size)
		return true;
	else
		return false;
	
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if (size == capacity)
		return true;
	else
		return false;
	
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for (int index = 1; index < size + 1; index++) {
		cout << "Priority: " << heap[index]->priority 
		<< " Description: " << heap[index]->description << endl;
	}

}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (!size)
		return TaskItem(-1, "NULL");
	else {
		int max = 0;
		TaskItem* temp = NULL;
		for (int index = 1; index < size + 1; index++) {
			if (max < heap[index]->priority) {
				max = heap[index]->priority;
				temp = heap[index];
			}
		}
		return *temp;
	}
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
	// returns false if queue is full
	if (size == capacity)
		return false;
	// base case: queue is empty
	if (!size)
		heap[1] = new TaskItem(val);
	// general case
	else {
		int i = size + 1;
		heap[i] = new TaskItem(val);
		while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
			TaskItem* temp = heap[i];
			heap[i] = heap[i/2];
			heap[i/2] = temp;
			i /= 2;
		}
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	// returns false if queue is empty
	if (!size)
		return false;
	// base case: only one element in the queue
	else if (size == 1) {
		delete heap[1];
		heap[1] = NULL;
	}
	// general case
	else {
		// move root down to last position
		TaskItem* first = heap[1];
		heap[1] = heap[size];
		heap[size] = first;
		// delete former root
		delete heap[size];
		heap[size] = NULL;
		int i = 1, left_or_right = 0;

		while (i < size-1) {
			// if there are only 2 elements, put higher priority first
			if (size-1 < 3) {
				if (heap[1]->priority < heap[2]->priority) {
					TaskItem* temp = heap[1];
					heap[1] = heap[2];
					heap[2] = temp;
				}
				else {
					i = size;
				}
			}
			
			else {
				// checks if right side or left side has higher priority
				if (heap[i*2]->priority < heap[i*2+1]->priority)
					left_or_right = 1;
				else
					left_or_right = 0;
				// if parent is less than child, swap parent and child
				if (heap[i]->priority < heap[i*2+left_or_right]->priority) {
					TaskItem* temp = heap[i];
					heap[i] = heap[i*2+left_or_right];
					heap[i*2+left_or_right] = temp;
					i = i*2+left_or_right;
				}
				else
					i = size;
				}
		}

	}
	size--;
	return true;
}
