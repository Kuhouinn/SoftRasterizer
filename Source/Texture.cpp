#include "Texture.h"
#include "stb_image.h"

#include <cmath>

Vector4 Texture::TextureSamplingNearest(Vector2 uv)
{
	unsigned char r = 255, g = 255, b = 255, a = 255;

	int x = 0, y = 0;

	//这std::round也太耗性能了吧，先注释掉，之后在看看怎么回事
//   	x = std::round(uv.x * (width - 1));
//   	y = std::round(uv.y * (height - 1));
	x = (uv.x * (width - 1));
	y = (uv.y * (height - 1));

	ReadPixel(x, y, r, g, b, a);

	float denom = 1.0f / 255.0f;
	float fr = r * denom;
	float fg = g * denom;
	float fb = b * denom;
	float fa = a * denom;

	Vector4 result{ fr, fg, fb, fa };
	return  result;
}

void Texture::ReadPixel(int u, int v, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const
{
	if (u < 0 || u >= width || v < 0 || v >= height)
	{
		return;
	}

	int index = (v * height + u) * channle;
// 	auto p = data.data();
// 	r = *(p + index);
// 	g = *(p + index + 1);
// 	b = *(p + index + 2);
// 	a = (channle >= 4) ? *(p + index + 3) : a;

	r = data[index + 0];
	g = data[index + 1];
	b = data[index + 2];
	a = (channle >= 4) ? data[index + 3] : a;

	return;
}
