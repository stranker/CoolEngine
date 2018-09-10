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
	void Dispose();
private:
	Material * material;
	unsigned int bufferData;	
	float* vertices;
	int vtxCount;
	bool shouldDispose;
	int vtxSize;
};

