#pragma once

#include "Exports.h"
#include <iostream>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Definitions.h"






class ENGINEDLL_API ModelImporter 
{
public:
	ModelImporter();
	~ModelImporter();
	static std::vector<ModelData> LoadMesh(const std::string& Filename);

private:	
	static ModelData InitMesh(unsigned int Index, const aiMesh* paiMesh);
	static std::vector<ModelData> GetModelData(const aiScene* pScene, const std::string& Filename);
};

