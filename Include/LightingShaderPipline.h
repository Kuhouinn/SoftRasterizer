#pragma once

#include "ShaderPipeline.h"

class DirectionalLight;

class LightingShaderPipline : public ShaderPipeline
{
public:

	LightingShaderPipline() {};

	virtual void VertexShader(VertexData& vertex);

	virtual void FragmentShader(const VertexData& data, Vector4& fragColor);

	void SetDirectionalLight(std::shared_ptr<DirectionalLight> light) { directionalLight = light; }

	void SetViewPosition(const Vector3& position) { viewPosition = position; }

private:
	std::shared_ptr<DirectionalLight> directionalLight = nullptr;

	Vector3 viewPosition;

	float diff = 0.0f;
	float spec = 0.0f;
};

