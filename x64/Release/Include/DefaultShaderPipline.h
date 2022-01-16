#pragma once
#include "ShaderPipeline.h"

class DefaultShaderPipline : public ShaderPipeline
{
public:

	virtual void VertexShader(VertexData& vertex);

	virtual void FragmentShader(const VertexData& data, Vector4& fragColor);
};

