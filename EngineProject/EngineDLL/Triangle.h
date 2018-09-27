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
private:
	Material * material;
	unsigned int bufferData;	
	float* vertices;
	int vtxCount;
	bool shouldDispose;
	int vtxSize;
	unsigned int programID;
	void UpdateModelMatrix();
};

