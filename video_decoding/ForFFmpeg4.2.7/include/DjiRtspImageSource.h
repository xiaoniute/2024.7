#pragma once

#include <cstdint>
#include <functional>
#include <string>

class DjiRtspImageSource
{
public:
	static const int PixelFormatNone = 0;
	static const int PixelFormatI420 = 1;
	static const int PixelFormatNV12 = 2;
	static const int PixelFormatNV21 = 3;
	static const int PixelFormatYV12 = 4;
	static const int PixelFormatRGB  = 5;
public:
	using ImageCallback = std::function<void(void* handler, uint8_t* frmdata, int frmsize, int width, int height, int pixfmt)>;
public:
	DjiRtspImageSource(const std::string& url);
	virtual ~DjiRtspImageSource();
public:
	int start();
	int stop();
	void setImageCallback(void* handler, ImageCallback cb);
private:
	void* mImpl;
};
