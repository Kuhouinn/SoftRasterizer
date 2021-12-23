#pragma once

#include "Vector3.h"
#include "Vector2.h"

#include <string>
#include <vector>

struct Vertex 
{
	// position
	Vector3 position;
	// normal
	Vector3 normal;
	// texCoords
	Vector2 texCoords;
	// tangent
	Vector3 tangent;
	// bitangent
	Vector3 bitangent;
};

struct Texture 
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	// mesh Data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
	}
};
