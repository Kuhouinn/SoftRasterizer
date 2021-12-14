#include "FrameBuffer.h"
#include "Vector4.h"

FrameBuffer::FrameBuffer(unsigned int widthVal /*= 1920*/, unsigned int heightVal /*= 1080*/) :width(widthVal), height(heightVal)
{
	colorBuffer.resize(widthVal * heightVal * 4);
	depthBuffer.resize(widthVal * heightVal);
}

void FrameBuffer::WritePixelColor(unsigned int x, unsigned int y, const Vector4& color)
{
// 	colorBuffer[0] = color.x;
// 	colorBuffer[1] = color.y;
// 	colorBuffer[2] = color.z;
// 	colorBuffer[3] = color.w;
}

void FrameBuffer::WriteDepth(unsigned int x, unsigned int y, float depth)
{

}
