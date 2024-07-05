#pragma once

#include <cstdint>

class TTARtspServer
{
public:
	TTARtspServer(int port, const char* mounts);
	TTARtspServer(int port);
	virtual ~TTARtspServer();
public:
	int start();
	int stop();
	void pushH264(uint8_t* data, int size);
	void setExtraData(uint8_t* data, int size);
private:
	void* mPusher;
};

