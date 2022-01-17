#include "FrameBuffer.h"
#include "Vector4.h"

FrameBuffer::FrameBuffer(unsigned int widthVal /*= 1920*/, unsigned int heightVal /*= 1080*/) :width(widthVal), height(heightVal)
{
	colorBuffer.resize(widthVal * heightVal);
	depthBuffer.resize(widthVal * heightVal);
}

void FrameBuffer::WritePixelColor(unsigned int x, unsigned int y, const Vector4& color)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		return;
	}

	auto r = unsigned char(color.x * 255);
	auto g = unsigned char(color.y * 255);
	auto b = unsigned char(color.z * 255);
	auto a = unsigned char(color.w * 255);

	unsigned int val = 0;
	val = val | a;
	val = val << 8 | r;
	val = val << 8 | g;
	val = val << 8 | b;

//	colorBuffer[y * width + x] = val;
	auto colorPtr = colorBuffer.data();
	*(colorPtr + y * width + x) = val;
}

void FrameBuffer::WriteDepth(unsigned int x, unsigned int y, float depth)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		return;
	}

//	depthBuffer[y * width + x] = depth;
	auto depthPtr = depthBuffer.data();
	*(depthPtr + y * width + x) = depth;
}

void FrameBuffer::Clear(const Vector4& clearColor)
{
	auto r = unsigned char(clearColor.x * 255);
	auto g = unsigned char(clearColor.y * 255);
	auto b = unsigned char(clearColor.z * 255);
	auto a = unsigned char(clearColor.w * 255);

	unsigned int val = 0;
	val = val | a;
	val = val << 8 | r;
	val = val << 8 | g;
	val = val << 8 | b;

// 	auto data = colorBuffer.data();
// 	auto depthData = depthBuffer.data();
// 
//  	for (auto y = 0; y < height; y++)
// 	{
// 		for (auto x = 0; x < width; x++)
// 		{
// 			long index = y * width + x;
// 			colorBuffer[index] = val;
// 			depthBuffer[index] = 1.0f;
// 		}
// 	}

 	colorBuffer.assign(width * height, val);
 	depthBuffer.assign(width * height, 1.0f);

}

float FrameBuffer::ReadDepth(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return 0.0f;
	}

	return depthBuffer[width * y + x];
}
