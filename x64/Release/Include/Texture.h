#pragma once

#include "Vector2.h"
#include "Vector4.h"

#include <string>
#include <vector>

class Texture
{
public:
	Texture() {};

	Vector4 TextureSamplingNearest(Vector2 uv);

private:
	void ReadPixel(int u, int v, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const;


public:
	std::string type;
	std::string path;
	int width = 0;
	int height = 0;
	int channle = 0;
	std::vector<unsigned char> data;
};

