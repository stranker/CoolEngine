#pragma once
#include "Entity.h"
#include "Material.h"
class ENGINEDLL_API Triangle : public Entity
{
public:
	Triangle(Renderer* _renderer);
	~Triangle();		
	void Draw() override;
	void SetVertices(float* _vertices, int count);
	void SetMaterial(Material* _material);	
	void Dispose();
	void BindMaterial();
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);	
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetColorVertices(float* vertices);
private:
	Material * material;
	unsigned int bufferData;	
	unsigned int bufferColor;
	unsigned int programID;
	float* vertices;
	float* verticesColor;
	bool shouldDispose;
	int vtxCount;
	int vtxSize;
	void UpdateModelMatrix();
};

