#pragma once
#include "Entity.h"
#include "Material.h"
class Triangle : public Entity
{
public:
	Triangle(Material* _material,Renderer* _renderer);
	~Triangle();		
	void SetVertices(float* _vertices, int count);
	void Draw() override;
	void Dispose();
private:
	Material * material;
	unsigned int bufferData;	
	float* vertices;
	int vtxCount;
	bool shouldDispose;
	int vtxSize;
};

