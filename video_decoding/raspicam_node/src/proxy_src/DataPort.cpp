#include "DataPort.h"

DataPort::DataPort()
{
}

DataPort::~DataPort()
{
}

BufferItem* DataPort::recv()
{
	return mIncomeBuffer.pop();
}

void DataPort::send(BufferItem* item)
{
	mOutcomeBuffer.push(item);
}

BufferItem* DataPort::outcome()
{
	return mOutcomeBuffer.pop();
}

void DataPort::income(BufferItem* item)
{
	mIncomeBuffer.push(item);
}

int DataPort::getIncomeSize()
{
	return mIncomeBuffer.getSize();
}

int DataPort::getOutcomeSize()
{
	return mOutcomeBuffer.getSize();
}