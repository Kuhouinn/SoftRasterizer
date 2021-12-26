#pragma once
#include <vector>
#include <string>
#include <assimp/scene.h>

#include "Mesh.h"

class Model
{
public:
	Model(const char* path);
	//void Draw(Shader shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

public:
	std::vector<Mesh> meshs;
	std::string directory;
	std::vector<Texture> textures_loaded;
};