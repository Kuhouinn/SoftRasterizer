#pragma once
#include <vector>
#include <string>
#include <assimp/scene.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model(const char* path);
	//void Draw(Shader shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	void TextureFromFile(const char* path, const std::string& directory, Texture& texture, bool gamma = false);

public:
	std::vector<Mesh> meshs;
	std::string directory;
	std::vector<std::shared_ptr<Texture>> textures_loaded;
};