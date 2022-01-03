#include "Model.h"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <glad/glad.h> 

Model::Model(const char* path)
{
	loadModel(path);
}

// void Model::Draw(Shader shader)
// {
// 	for (int i = 0; i < meshs.size(); i++)
// 	{
// 		meshs[i].Draw(shader);
// 	}
// }

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshs.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//载入Mesh的vertice数据
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords = Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}

		vertices.push_back(vertex);
	}

	//载入Mesh的indices数据
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace* face = &mesh->mFaces[i];

		for (int j = 0; j < face->mNumIndices; j++)
		{
			indices.push_back(face->mIndices[j]);
		}
	}

	//载入textures数据
	if (mesh->mMaterialIndex)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());
		std::vector<Texture> specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMap.begin(), specularMap.end());
	}

	return Mesh(vertices, indices, textures);

}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		Texture texture;
		aiString path;
		mat->GetTexture(type, i, &path);
		bool skip = false;
		for (int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), path.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			texture.id = TextureFromFile(path.C_Str(), directory);
			texture.type = typeName;
			texture.path = path.C_Str();

			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID=0;
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
// 	if (data)
// 	{
// 		GLenum format, formatAlpha;
// 		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
// 		switch (nrComponents)
// 		{
// 		case 1:
// 			format = GL_RED;
// 			break;
// 		case 3:
// 			format = GL_RGB;
// 			formatAlpha = GL_RGB8;
// 			break;
// 		case 4:
// 			format = GL_RGBA;
// 			formatAlpha = GL_RGBA8;
// 			break;
// 		default:
// 			format = GL_RGB;
// 			formatAlpha = GL_RGB8;
// 		}
// 
// 		glBindTexture(GL_TEXTURE_2D, textureID);
// 		glTextureStorage2D(textureID, 5, formatAlpha, width, height);
// 		//glBindTextureUnit(0, textureID);
// 		glTextureSubImage2D(textureID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
// 		glGenerateTextureMipmap(textureID);
// 
// 		glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 		glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 		stbi_image_free(data);
// 	}
// 	else
// 	{
// 		std::cout << "Texture failed to load at path: " << path << std::endl;
// 		stbi_image_free(data);
// 	}

	return textureID;
}