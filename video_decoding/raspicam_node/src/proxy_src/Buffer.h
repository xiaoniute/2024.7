#pragma once
#include <list>
#include "BufferItem.h"
#include "Lock.h"

class Buffer
{
public:
	Buffer();
	Buffer(int capacity);
	virtual ~Buffer();
	void push(BufferItem* item);
	BufferItem* pop();
	void clear();
	int getSize();
	int getCapacity();
private:
	void dropLocked();
	void pushLocked(BufferItem* item);
	BufferItem* popLocked();
private:
	std::list<BufferItem*> queue;
	int capacity;
	int size;
	int mQueueSize;
	Lock lock;
};

