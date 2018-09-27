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
<<<<<<< HEAD
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);	
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetColorVertices(float* vertices);
=======
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
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
<<<<<<< HEAD
	void UpdateModelMatrix();
=======
	unsigned int programID;
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
};

