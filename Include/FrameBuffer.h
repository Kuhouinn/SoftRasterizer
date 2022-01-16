#pragma once
#include <vector>

class Vector4;

class FrameBuffer
{
public:
	FrameBuffer(unsigned int widthVal = 1920, unsigned int heightVal = 1080);

	//x,y取值范围是[0,width),[0,height)
	void WritePixelColor(unsigned int x, unsigned int y, const Vector4& color);

	void WriteDepth(unsigned int x, unsigned int y, float depth);

	//使用清除颜色覆盖所有像素
	void Clear(const Vector4& clearColor);

	unsigned int GetWidth()const { return width; }

	unsigned int GetHeight()const { return height; }

	const auto& GetColorBuffer() const{ return colorBuffer; }

	float ReadDepth(int x,int y) const;


private:
	unsigned int width = 1920;
	unsigned int height = 1080;
	std::vector<float> depthBuffer;          
	std::vector<unsigned int> colorBuffer;

};

