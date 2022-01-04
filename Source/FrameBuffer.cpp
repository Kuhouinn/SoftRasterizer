#include "FrameBuffer.h"
#include "Vector4.h"

FrameBuffer::FrameBuffer(unsigned int widthVal /*= 1920*/, unsigned int heightVal /*= 1080*/) :width(widthVal), height(heightVal)
{
	colorBuffer.resize(widthVal * heightVal * 4);
	depthBuffer.resize(widthVal * heightVal);
}

void FrameBuffer::WritePixelColor(unsigned int x, unsigned int y, const Vector4& color)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		return;
	}

	//сп╢Щ╦д╫Ь
	auto r = unsigned char(color.x * 255);
	auto g = unsigned char(color.x * 255);
	auto b = unsigned char(color.x * 255);
	auto a = unsigned char(color.x * 255);

	auto index = (y * width + x) * 4;
	colorBuffer[index] = r;
	colorBuffer[index + 1] = g;
	colorBuffer[index + 2] = b;
	colorBuffer[index + 3] = a;
}

void FrameBuffer::WriteDepth(unsigned int x, unsigned int y, float depth)
{
	if (x >= width || y >= height || x < 0 || y < 0)
	{
		return;
	}

	auto index = y * width + x;
	depthBuffer[index] = depth;
}

void FrameBuffer::Clear(const Vector4& clearColor)
{
	auto r = unsigned char(clearColor.x * 255);
	auto g = unsigned char(clearColor.y * 255);
	auto b = unsigned char(clearColor.z * 255);
	auto a = unsigned char(clearColor.w * 255);

	for (auto y = 0; y < height; y++)
	{
		for (auto x = 0; x < width; x++)
		{
			auto index = (y * width + x) * 4;
			colorBuffer[index] = r;
			colorBuffer[index + 1] = g;
			colorBuffer[index + 2] = b;
			colorBuffer[index + 3] = a;

			depthBuffer[y * width + x] = 1.0f;
		}
	}
}

float FrameBuffer::ReadDepth(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return 0.0f;
	}

	return depthBuffer[height * y + x];
}
