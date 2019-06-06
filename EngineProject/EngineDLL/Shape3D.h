#pragma once
#include "Entity.h"
#include "Material.h"
#include "ModelImporter.h"
#include "Definitions.h"
#include "TextureImporter.h"

class ENGINEDLL_API Shape3D :
	public Entity
{
public:
	Shape3D(Renderer* _renderer, string modelPath);
	~Shape3D();
	void Draw() override;
	void SetVertices(float* _vertices, int count);
	void SetIndexes(unsigned int* _indexes, int count);
	virtual void SetMaterial(Material* _material);
	void Dispose();
	void BindMaterial();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetTexture(const char * imagepath);
	void SetVerticesUV(float* vertices);
	void MoveIn(float x, float y, float z);	
protected:
	Material * material;
	unsigned int bufferData;
	unsigned int bufferColor;
	unsigned int bufferIndex;
	unsigned int programID;
	float* vertices;
	float* verticesUVArray;
	ModelData mesh;
	unsigned int verticesUV;
	unsigned int* indexes;
	bool shouldDispose;
	int vtxCount;
	int vtxUvCount;
	int vtxSize;
	int indexCount;
	void UpdateModelMatrix();	
	void OnCollision() override {};
	void OnUpdate(float deltaTime) override {};
	unsigned int texture;
	int heightTotal;
	int widthTotal;
};

