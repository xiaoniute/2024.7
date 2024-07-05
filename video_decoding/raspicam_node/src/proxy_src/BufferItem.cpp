#include "BufferItem.h"


BufferItem::BufferItem(const char* data, int size):
	buffer(data, data+size),
	mPeerNo(0)
{
}

BufferItem::BufferItem(const char* data, int size, int remoteAddr):
	buffer(data, data+size),
	mPeerNo(remoteAddr)
{

}


BufferItem::~BufferItem()
{
}

char* BufferItem::data()
{
	return buffer.data();
}

int BufferItem::size()
{
	return buffer.size();
}

int BufferItem::mAdd(char *p, int len){
	for(int i=0; i<len; i++){
		buffer.push_back(p[i]);
	}
	
	return 0;
}

void BufferItem::endString(){
	buffer.push_back(0);
}
