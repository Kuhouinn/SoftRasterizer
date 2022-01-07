#include "ShaderPipeline.h"
#include "VertexData.h"
#include "Texture.h"

#include <cmath>
#include <algorithm>

std::vector<std::shared_ptr<Texture>> ShaderPipeline::textures = {};

bool InsideTriangle(const Vector3& p, const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
	//通过叉乘的方法判断点是否在三角形内。
	auto result1 = (p - v0).CrossProduct(v1 - v0);
	auto result2 = (p - v1).CrossProduct(v2 - v1);
	auto result3 = (p - v2).CrossProduct(v0 - v2);
	bool f1 = result1.z > 0;
	bool f2 = result2.z > 0;
	bool f3 = result3.z > 0;

	bool equal1 = result1.z == 0;
	bool equal2 = result2.z == 0;
	bool equal3 = result3.z == 0;

	//这个可能有改善，之前应该把在三角形上的点也去掉了。
	if (equal1 || equal2 || equal3)
	{
		return true;
	}

	if (f1 == f2 && f2 == f3)
	{
		return true;
	}

	return false;
}

void ShaderPipeline::RasterizeFillEdgeFunction(const VertexData& v0, const VertexData& v1, const VertexData& v2, unsigned int screenWidth, unsigned int screeneHeight, std::vector<VertexData>& rasterizedPoints)
{
	int minX = v0.screenPosition.x;
	int maxX = v0.screenPosition.x;
	int minY = v0.screenPosition.y;
	int maxY = v0.screenPosition.y;

	minX = std::min(minX, std::min(int(v1.screenPosition.x), int(v2.screenPosition.x)));
	maxX = std::max(maxX, std::max(int(v1.screenPosition.x), int(v2.screenPosition.x)));
	minY = std::min(minY, std::min(int(v1.screenPosition.y), int(v2.screenPosition.y)));
	maxY = std::max(maxY, std::max(int(v1.screenPosition.y), int(v2.screenPosition.y)));

	auto v10 = v1.screenPosition - v0.screenPosition;
	auto v20 = v2.screenPosition - v0.screenPosition;
	auto res = v10.x * v20.y - v10.y * v20.x;

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

			Vector3 p1 = { (float)v0.screenPosition.x,(float)v0.screenPosition.y,1.0 };
			Vector3 p2 = { (float)v1.screenPosition.x,(float)v1.screenPosition.y,1.0 };
			Vector3 p3 = { (float)v2.screenPosition.x,(float)v2.screenPosition.y,1.0 };

			Vector3 C = p - p3;
			Vector3 A = p1 - p3;
			Vector3 B = p2 - p3;

			float sp23 = C.CrossProduct(B).z;
			float sp123 = A.CrossProduct(B).z;
			float sp13 = C.CrossProduct(A).z;
			float spba = B.CrossProduct(A).z;

			float w1 = sp23 / sp123;
			float w2 = sp13 / spba;
			float w3 = 1 - w1 - w2;
			Vector3 test{ w1,w2,w3 };
//			if (std::abs(u.z) > 1e-2)
			{
				//Vector3 result(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
				Vector3 result(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
				auto point = VertexData::BarycentricLerp(v0, v1, v2, test);

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


// 	VertexData v[] = { v0, v1, v2 };
// 	//Edge-equations rasterization algorithm
// 	Vector2i bounding_min;
// 	Vector2i bounding_max;
// 	bounding_min.x = std::max(std::min(v0.screenPosition.x, std::min(v1.screenPosition.x, v2.screenPosition.x)), 0);
// 	bounding_min.y = std::max(std::min(v0.screenPosition.y, std::min(v1.screenPosition.y, v2.screenPosition.y)), 0);
// 	bounding_max.x = std::min(std::max(v0.screenPosition.x, std::max(v1.screenPosition.x, v2.screenPosition.x)), (int)screenWidth - 1);
// 	bounding_max.y = std::min(std::max(v0.screenPosition.y, std::max(v1.screenPosition.y, v2.screenPosition.y)), (int)screeneHeight - 1);
// 
// 	//Adjust the order
// 	{
// 		auto e1 = v1.screenPosition - v0.screenPosition;
// 		auto e2 = v2.screenPosition - v0.screenPosition;
// 		int orient = e1.x * e2.y - e1.y * e2.x;
// 		if (orient > 0)
// 		{
// 			std::swap(v[1], v[2]);
// 		}
// 	}
// 
// 	//Accelerated Half-Space Triangle Rasterization
// 	//Refs:Mileff P, Nehéz K, Dudra J. Accelerated half-space triangle rasterization[J].
// 	//     Acta Polytechnica Hungarica, 2015, 12(7): 217-236. http://acta.uni-obuda.hu/Mileff_Nehez_Dudra_63.pdf
// 
// 	const Vector2i& A = v[0].screenPosition;
// 	const Vector2i& B = v[1].screenPosition;
// 	const Vector2i& C = v[2].screenPosition;
// 
// 	const int I01 = A.y - B.y, I02 = B.y - C.y, I03 = C.y - A.y;
// 	const int J01 = B.x - A.x, J02 = C.x - B.x, J03 = A.x - C.x;
// 	const int K01 = A.x * B.y - A.y * B.x;
// 	const int K02 = B.x * C.y - B.y * C.x;
// 	const int K03 = C.x * A.y - C.y * A.x;
// 
// 	int F01 = I01 * bounding_min.x + J01 * bounding_min.y + K01;
// 	int F02 = I02 * bounding_min.x + J02 * bounding_min.y + K02;
// 	int F03 = I03 * bounding_min.x + J03 * bounding_min.y + K03;
// 
// 	//Degenerated to a line or a point
// 	if (F01 + F02 + F03 == 0)
// 		return;
// 
// 	const float one_div_delta = 1.0f / (F01 + F02 + F03);
// 
// 	//Top left fill rule
// 	int E1_t = (((B.y > A.y) || (A.y == B.y && A.x > B.x)) ? 0 : 0);
// 	int E2_t = (((C.y > B.y) || (B.y == C.y && B.x > C.x)) ? 0 : 0);
// 	int E3_t = (((A.y > C.y) || (C.y == A.y && C.x > A.x)) ? 0 : 0);
// 
// 	int Cy1 = F01, Cy2 = F02, Cy3 = F03;
// 	for (int y = bounding_min.y; y <= bounding_max.y; ++y)
// 	{
// 		int Cx1 = Cy1, Cx2 = Cy2, Cx3 = Cy3;
// 		for (int x = bounding_min.x; x <= bounding_max.x; ++x)
// 		{
// 			int E1 = Cx1 + E1_t, E2 = Cx2 + E2_t, E3 = Cx3 + E3_t;
// 			//Counter-clockwise winding order
// 			if (E1 <= 0 && E2 <= 0 && E3 <= 0)
// 			{
// 				Vector3 uvw(Cx2 * one_div_delta, Cx3 * one_div_delta, Cx1 * one_div_delta);
// 				auto rasterized_point = VertexData::BarycentricLerp(v[0], v[1], v[2], uvw);
// 				rasterized_point.screenPosition = Vector2i(x, y);
// 				rasterizedPoints.push_back(rasterized_point);
// 			}
// 			Cx1 += I01; Cx2 += I02; Cx3 += I03;
// 		}
// 		Cy1 += J01; Cy2 += J02; Cy3 += J03;
// 	}

}

Vector4 ShaderPipeline::Texture2D(unsigned int id, const Vector2& uv)
{
	if (id< 0|| id>textures.size())
	{
		return Vector4();
	}

	return textures[id]->TextureSamplingNearest(uv);
}

Vector3 ShaderPipeline::Reflect(const Vector3& l, const Vector3& n)
{
	return 2 * (l * n) * n - l;
}
