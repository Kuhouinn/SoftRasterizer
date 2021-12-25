#include "ShaderPipeline.h"
#include "VertexData.h"
#include <cmath>

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

	minX = std::min(minX, std::min(v1.screenPosition.x, v2.screenPosition.x));
	maxX = std::max(maxX, std::max(v1.screenPosition.x, v2.screenPosition.x));
	minY = std::min(minY, std::min(v1.screenPosition.y, v2.screenPosition.y));
	maxY = std::max(maxY, std::max(v1.screenPosition.y, v2.screenPosition.y));
	for (int ix = minX; ix <= maxX; ix++)
	{
		for (int iy = minY; iy <= maxY; iy++)
		{
			Vector3 p(ix, iy, 1.0);

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
				auto point = VertexData::barycentricLerp(v0, v1, v2, result);

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
