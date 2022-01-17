#include "ShaderPipeline.h"
#include "VertexData.h"
#include "Texture.h"

#include <cmath>
#include <algorithm>

void ShaderPipeline::ComputePoint(const VertexData& begin, const VertexData& end, const unsigned int& screenWidth, const unsigned int& screeneHeight, std::vector<VertexData>& rasterizedPoints)
{
	//Bresenham line rasterization

	int dx = end.screenPosition.x - begin.screenPosition.x;
	int dy = end.screenPosition.y - begin.screenPosition.y;
	int stepX = 1, stepY = 1;

	// judge the sign
	if (dx < 0)
	{
		stepX = -1;
		dx = -dx;
	}
	if (dy < 0)
	{
		stepY = -1;
		dy = -dy;
	}

	int d2x = 2 * dx, d2y = 2 * dy;
	int d2y_minus_d2x = d2y - d2x;
	int sx = begin.screenPosition.x;
	int sy = begin.screenPosition.y;

	// slope < 1.
	if (dy <= dx)
	{
		int flag = d2y - dx;
		for (int i = 0; i <= dx; ++i)
		{
			auto mid = VertexData::Lerp(begin, end, static_cast<float>(i) / dx);
			mid.screenPosition = Vector2i(sx, sy);
			if (mid.screenPosition.x >= 0 && mid.screenPosition.x <= screenWidth && mid.screenPosition.y >= 0 && mid.screenPosition.y <= screeneHeight)
			{
				rasterizedPoints.push_back(mid);
			}
			sx += stepX;
			if (flag <= 0)
			{
				flag += d2y;
			}
			else
			{
				sy += stepY;
				flag += d2y_minus_d2x;
			}
		}
	}
	// slope > 1.
	else
	{
		int flag = d2x - dy;
		for (int i = 0; i <= dy; ++i)
		{
			auto mid = VertexData::Lerp(begin, end, static_cast<float>(i) / dy);
			mid.screenPosition = Vector2i(sx, sy);
			if (mid.screenPosition.x >= 0 && mid.screenPosition.x < screenWidth && mid.screenPosition.y >= 0 && mid.screenPosition.y < screeneHeight)
			{
				rasterizedPoints.push_back(mid);
			}
			sy += stepY;
			if (flag <= 0)
			{
				flag += d2x;
			}
			else
			{
				sx += stepX;
				flag -= d2y_minus_d2x;
			}
		}
	}
}

std::vector<std::shared_ptr<Texture>> ShaderPipeline::textures = {};

std::vector<int> ShaderPipeline::RasterizeTriangle(const VertexData& v0, const VertexData& v1, const VertexData& v2, unsigned int screenWidth, unsigned int screeneHeight, std::vector<VertexData>& rasterizedPoints)
{
	int minX = v0.screenPosition.x;
	int maxX = v0.screenPosition.x;
	int minY = v0.screenPosition.y;
	int maxY = v0.screenPosition.y;
	
	minX = std::max(std::min(v0.screenPosition.x, std::min(v1.screenPosition.x, v2.screenPosition.x)), 0);
	minY = std::max(std::min(v0.screenPosition.y, std::min(v1.screenPosition.y, v2.screenPosition.y)), 0);
	maxX = std::min(std::max(v0.screenPosition.x, std::max(v1.screenPosition.x, v2.screenPosition.x)), (int)screenWidth - 1);
	maxY = std::min(std::max(v0.screenPosition.y, std::max(v1.screenPosition.y, v2.screenPosition.y)), (int)screeneHeight - 1);

	std::vector<int> boundingBox{ minX,minY,maxX,maxY };
	
	auto v10 = v1.screenPosition - v0.screenPosition;
	auto v20 = v2.screenPosition - v0.screenPosition;
	auto res = v10.x * v20.y - v10.y * v20.x;
	
	Vector2i arr[3] = { {v0.screenPosition.x,v0.screenPosition.y},{v1.screenPosition.x,v1.screenPosition.y}, {v2.screenPosition.x,v2.screenPosition.y} };
	
#pragma omp parallel for
	for (int ix = minX; ix < maxX; ix++)
	{
		for (int iy = minY; iy < maxY; iy++)
		{
			Vector2i p(ix, iy);
			Vector2i p0p2 = v2.screenPosition - v0.screenPosition;
			Vector2i p0p = p - v0.screenPosition;
			Vector2i p2p1 = v1.screenPosition - v2.screenPosition;
			Vector2i p2p = p - v2.screenPosition;
			Vector2i p1p0 = v0.screenPosition - v1.screenPosition;
			Vector2i p1p = p - v1.screenPosition;
	
			int tmp1 = p0p2.x * p0p.y - p0p.x * p0p2.y;
			int tmp2 = p2p1.x * p2p.y - p2p.x * p2p1.y;
			int tmp3 = p1p0.x * p1p.y - p1p.x * p1p0.y;
	
			//v0,v1,v2是顺时针顺序排列的，但tmp1，tmp2，tmp3是按逆时针计算的向量。
			bool condition1 = tmp1 >= 0 && tmp2 >= 0 && tmp3 >= 0; // 逆时针三角形
	
			if (condition1)
			{
				// 重心坐标
	 			Vector3 vx = Vector3(-p1p0.x, p0p2.x, -p0p.x);
	 			Vector3 vy = Vector3(-p1p0.y, p0p2.y, -p0p.y);
				Vector3 cpResult = vx.CrossProduct(vy);
				Vector3 result;
				result.y = cpResult.x / cpResult.z;
				result.z = cpResult.y / cpResult.z;
				result.x = 1 - result.y - result.z;
	
				auto point = VertexData::BarycentricLerp(v0, v1, v2, result);
				point.screenPosition = p;
	
				if (point.screenPosition.x<0 || point.screenPosition.x>screenWidth || point.screenPosition.y<0 || point.screenPosition.y >screeneHeight)
				{
					continue;
				}
	
//				rasterizedPoints.emplace_back(point);
 				point.discard = false;
 				rasterizedPoints[iy * screenWidth + ix] = point;
			}
		}
	}

	return boundingBox;
}

void ShaderPipeline::RasterizeLine(const VertexData& v0, const VertexData& v1, const VertexData& v2, unsigned int screenWidth, unsigned int screeneHeight, std::vector<VertexData>& rasterizedPoints)
{
	ComputePoint(v0, v1, screenWidth, screeneHeight, rasterizedPoints);
	ComputePoint(v1, v2, screenWidth, screeneHeight, rasterizedPoints);
	ComputePoint(v0, v2, screenWidth, screeneHeight, rasterizedPoints);
}

Vector4 ShaderPipeline::Texture2D(unsigned int id, const Vector2& uv)
{
	if (id< 0 || id>textures.size())
	{
		return Vector4();
	}

	return std::move(textures[id]->TextureSamplingNearest(uv));
}

Vector3 ShaderPipeline::Reflect(const Vector3& l, const Vector3& n)
{
	return 2 * (l * n) * n - l;
}
