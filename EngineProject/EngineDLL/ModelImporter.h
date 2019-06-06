#pragma once

#include "Exports.h"
#include <iostream>
#include <GL/glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"



struct Vertex
{
	glm::vec3 m_pos;
	glm::vec2 m_tex;
	glm::vec3 m_normal;

	Vertex() {}

	Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};

struct ModelData
{
	std::vector<Vertex> v;
	std::vector<unsigned int> i;
};


class ENGINEDLL_API ModelImporter 
{
public:
	ModelImporter();
	~ModelImporter();
	std::vector<ModelData> LoadMesh(const std::string& Filename);

	struct MeshEntry {
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};
	std::vector<MeshEntry> m_Entries;
private:	
	ModelData InitMesh(unsigned int Index, const aiMesh* paiMesh);
	std::vector<ModelData> GetModelData(const aiScene* pScene, const std::string& Filename);
};

