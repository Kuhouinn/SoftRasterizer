#include "LightingShaderPipline.h"
#include "VertexData.h"
#include "DirectionalLight.h"

#include <algorithm>
#include <cmath>

#include <chrono>

void LightingShaderPipline::VertexShader(VertexData& vertex)
{
	vertex.position = modelMatrix * vertex.position;
	vertex.clipPosition = projectionMatrix * viewMatrix * vertex.position;

	Vector3 lightDir = (-directionalLight->direction).Normalize();
	Vector3 normal = vertex.normal.Normalize();

	diff = std::max(normal * lightDir, 0.0f);

	Vector3 viewDir = (viewPosition - Vector3{ vertex.position.x, vertex.position.y, vertex.position.z }).Normalize();
	Vector3 relectDir = Reflect(-lightDir, normal);

	spec = std::pow(std::max(viewDir * relectDir, 0.0f), 32);

}

void LightingShaderPipline::FragmentShader(const VertexData& data, Vector4& fragColor)
{
	Vector3 lightDir = (-directionalLight->direction).Normalize();
	Vector3 normal = data.normal.Normalize();

	diff = std::max(normal * lightDir, 0.0f);

	Vector3 viewDir = (viewPosition - Vector3{ data.position.x, data.position.y, data.position.z }).Normalize();
	Vector3 relectDir = Reflect(-lightDir, normal);

	spec = std::pow(std::max(viewDir * relectDir, 0.0f), 32);

	auto diffColor = Texture2D(diffuseTextureId, data.texCoordinate);
	Vector3 ambient = Vector3{ directionalLight->amibent.x * diffColor.x,directionalLight->amibent.y * diffColor.y,directionalLight->amibent.z * diffColor.z };

	Vector3 diffuse = Vector3{ directionalLight->diffuse.x * diffColor.x,directionalLight->diffuse.y * diffColor.y,directionalLight->diffuse.z * diffColor.z };
	diffuse *= diff;

	auto specColor = Texture2D(specularTextureId, data.texCoordinate);
	Vector3 specular = Vector3{ directionalLight->specular.x * specColor.x,directionalLight->specular.y * specColor.y,directionalLight->specular.z * specColor.z };
	specular *= spec;

 	Vector3 finalColor = ambient + diffuse + specular;

	fragColor = Vector4(std::min(finalColor.x,1.0f), std::min(finalColor.y,1.0f), std::min(finalColor.z,1.0f));

}
