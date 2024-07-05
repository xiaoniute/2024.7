#include "Buffer.h"
#include "Log.h"

#define DEFAULT_CAPACITY 2000000

Buffer::Buffer() :
	capacity(DEFAULT_CAPACITY),
	size(0),
	mQueueSize(0)
{

}

Buffer::Buffer(int capacity):
	capacity(capacity),
	size(0),
	mQueueSize(0)
{
}

Buffer::~Buffer()
{
	clear();
}

int Buffer::getSize()
{
	int s = 0;
	lock.lock();
	s = size;
	lock.unlock();
	return s;
}

int Buffer::getCapacity()
{
	int c = 0;
	lock.lock();
	c = capacity;
	lock.unlock();
	return c;
}

void Buffer::push(BufferItem* item) {
	lock.lock();
	pushLocked(item);
	dropLocked();
	lock.unlock();
}

void Buffer::pushLocked(BufferItem* item)
{
	if (item) {
		queue.push_back(item);
		mQueueSize++;
		size += item->size();
	}
}

BufferItem* Buffer::pop() {
	BufferItem* item = NULL;
	lock.lock();
	item = popLocked();
	lock.unlock();
	return item;
}

BufferItem* Buffer::popLocked()
{
	if (mQueueSize > 0) {
		BufferItem* front = queue.front();
		queue.pop_front();
		mQueueSize--;
		size -= front->size();
		return front;
	}else{
		return NULL;
	}
}

void Buffer::dropLocked()
{
	while (size > capacity) {
		BufferItem* item = popLocked();
		if (item) {
			Log::w("Buffer overflow, droped %d bytes", item->size());
			delete item;
		}
		else {
			break;
		}
	}
}

void Buffer::clear()
{
	BufferItem* item = NULL;
	lock.lock();
	while ((item = popLocked()) != NULL) {
		if (item) {
			delete item;
		}
	}
	lock.unlock();
}
