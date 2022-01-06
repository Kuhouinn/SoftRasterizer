#pragma once
#include <vector>
#include <memory>

#include "Matrix4.h"

struct VertexData;

class Texture;
class Vector2;

class ShaderPipeline
{
public:

	virtual void VertexShader(VertexData& vertex) {};

	virtual void FragmentShader(const VertexData& data, Vector4& fragColor) {};

	const Matrix4& GetModelMatrix() const { return modelMatrix; }
	void SetModelMatrix(const Matrix4& model) { modelMatrix = model; }

	const Matrix4& GetViewMatrix() const { return viewMatrix; }
	void SetViewMatrix(const Matrix4& view) { viewMatrix = view; }

	const Matrix4& GetProjectionMatrix() const { return projectionMatrix; }
	void SetProjectionMatrix(const Matrix4& projection) { projectionMatrix = projection; }

	void SetDiffuseTexId(int id) { diffuseTextureId = id; }

	void SetSpecularTexId(int id) { specularTextureId = id; }

	void UploadTexture(std::shared_ptr<Texture> texture) { textures.push_back(texture); }

	void ClearTextures() { textures.clear(); }

	//三角形光栅化,使用Fill Edge 
	static void RasterizeFillEdgeFunction(
		const VertexData& v0,
		const VertexData& v1,
		const VertexData& v2,
		unsigned int screenWidth,
		unsigned int screeneHeight,
		std::vector<VertexData>& rasterizedPoints);

	static Vector4 Texture2D(unsigned int id, const Vector2& uv);

	static Vector3 Reflect(const Vector3& l, const Vector3& n);

protected:
	Matrix4 modelMatrix;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;

	int diffuseTextureId = -1;
	int specularTextureId = -1;

	static std::vector<std::shared_ptr<Texture>> textures;
};

