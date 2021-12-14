#pragma once
#include <vector>

class Vector4;

class FrameBuffer
{
public:
	FrameBuffer(unsigned int widthVal = 1920, unsigned int heightVal = 1080);

	void WritePixelColor(unsigned int x, unsigned int y, const Vector4& color);

	void WriteDepth(unsigned int x, unsigned int y, float depth);


private:
	unsigned int width = 1920;
	unsigned int height = 1080;
	std::vector<double> depthBuffer;          
	std::vector<unsigned char> colorBuffer;

};

