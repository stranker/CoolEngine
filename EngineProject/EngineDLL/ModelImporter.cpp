#include "ModelImporter.h"



ModelImporter::ModelImporter()
{
}


ModelImporter::~ModelImporter()
{
}

std::vector<ModelData> ModelImporter::LoadMesh(const std::string& Filename)
{
	// Release the previously loaded mesh (if it exists)
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	return GetModelData(pScene, Filename);
	
}

std::vector<ModelData> ModelImporter::GetModelData(const aiScene* pScene, const std::string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	std::vector<ModelData> models;
	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		models.push_back(InitMesh(i, paiMesh));
	}
	return models;
}


ModelData ModelImporter::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Vertex v{ glm::vec3(pPos->x, pPos->y, pPos->z),
					glm::vec2(pTexCoord->x, pTexCoord->y),
					glm::vec3(pNormal->x, pNormal->y, pNormal->z)
		};

		Vertices.push_back(v);

		for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
			const aiFace& Face = paiMesh->mFaces[i];
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
		}
		ModelData aux;
		aux.v = Vertices;
		aux.i = Indices;
		return aux;
	}
}

