#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model(const char* path);
	~Model();

	void draw(Camera* ca, const std::vector<Light>& lights, Light& spotlight);
private:
	void loadModel(const std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	std::string _path;
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
};

