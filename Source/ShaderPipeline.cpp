#include "ShaderPipeline.h"
#include "VertexData.h"
#include "Texture.h"

#include <cmath>
#include <algorithm>

std::vector<std::shared_ptr<Texture>> ShaderPipeline::textures = {};

bool InsideTriangle(const Vector3& p, const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
	//通过叉乘的方法判断点是否在三角形内。
	bool f1 = (p - v0).CrossProduct(v1 - v0).z > 0;
	bool f2 = (p - v1).CrossProduct(v2 - v1).z > 0;
	bool f3 = (p - v2).CrossProduct(v0 - v2).z > 0;
	if (f1 == f2 && f2 == f3)
	{
		return true;
	}

	return false;
}

void ShaderPipeline::RasterizeFillEdgeFunction(const VertexData& v0, const VertexData& v1, const VertexData& v2, unsigned int screenWidth, unsigned int screeneHeight, std::vector<VertexData>& rasterizedPoints)
{
	//Edge-function rasterization algorithm

		//Task4: Implement edge-function triangle rassterization algorithm
		// Note: You should use VertexData::barycentricLerp(v0, v1, v2, w) for interpolation, 
		//       interpolated points should be pushed back to rasterized_points.
		//       Interpolated points shold be discarded if they are outside the window. 

		//       v0.screenPosition, v1.screenPosition and v2.screenPosition are the screen space vertices.
	int minX = v0.screenPosition.x;
	int maxX = v0.screenPosition.x;
	int minY = v0.screenPosition.y;
	int maxY = v0.screenPosition.y;

	minX = std::min(minX, std::min(int(v1.screenPosition.x), int(v2.screenPosition.x)));
	maxX = std::max(maxX, std::max(int(v1.screenPosition.x), int(v2.screenPosition.x)));
	minY = std::min(minY, std::min(int(v1.screenPosition.y), int(v2.screenPosition.y)));
	maxY = std::max(maxY, std::max(int(v1.screenPosition.y), int(v2.screenPosition.y)));
	for (int ix = minX; ix <= maxX; ix++)
	{
		for (int iy = minY; iy <= maxY; iy++)
		{
			Vector3 p(ix, iy, 1.0);
			Vector3 vs0(v0.screenPosition.x, v0.screenPosition.y, 1.0f);
			Vector3 vs1(v1.screenPosition.x, v1.screenPosition.y, 1.0f);
			Vector3 vs2(v2.screenPosition.x, v2.screenPosition.y, 1.0f);

			if (!InsideTriangle(p, vs0, vs1, vs2))
			{
				continue;
			}

			Vector3 s[2];
			s[1].x = v2.screenPosition.y - v0.screenPosition.y;
			s[1].y = v1.screenPosition.y - v0.screenPosition.y;
			s[1].z = v0.screenPosition.y - p.y;

			s[0].x = v2.screenPosition.x - v0.screenPosition.x;
			s[0].y = v1.screenPosition.x - v0.screenPosition.x;
			s[0].z = v0.screenPosition.x - p.x;


			Vector3 u = s[0].CrossProduct(s[1]);

			if (std::abs(u.z) > 1e-2)
			{
				Vector3 result(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
				auto point = VertexData::BarycentricLerp(v0, v1, v2, result);

				if (point.screenPosition.x<0 || point.screenPosition.x>screenWidth || point.screenPosition.y<0 || point.screenPosition.y >screeneHeight)
				{
					continue;
				}

				rasterizedPoints.push_back(point);
			}
		}
	}


	//For instance:
	rasterizedPoints.push_back(v0);
	rasterizedPoints.push_back(v1);
	rasterizedPoints.push_back(v2);
}

Vector4 ShaderPipeline::Texture2D(unsigned int id, const Vector2& uv)
{
	if (id< 0|| id>textures.size())
	{
		return Vector4();
	}

	return textures[id]->TextureSamplingNearest(uv);
}
