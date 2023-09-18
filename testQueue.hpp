#define SIZE 10

#include <iostream>
#include <cstdlib>
using namespace std;


// Class for queue
class queue
{
public:
	int* arr;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue

public:
	queue(int size = SIZE); 	// constructor
	~queue();   				// destructor

	int dequeue();
	int enqueue(int x);
	int peek();
	int size();
	bool isEmpty();
	bool isFull();

    // getters
    int getCount() {
        return count;
    }

    // test functions
    void testSize();
    void testEmpty();
    void testFull();
    void testDequeueEmpty();
    void testDequeueNEmpty();
    void testEnqueueFull();
    void testEnqueueNFull();
    void testPeekEmpty();
    void testPeekNEmpty();
};