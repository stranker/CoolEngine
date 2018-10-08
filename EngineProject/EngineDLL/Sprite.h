#pragma once
#include "Shape.h"
class ENGINEDLL_API Sprite :
	public Shape
{
public:
	Sprite(Renderer * _renderer);
	~Sprite();
	void Draw() override;
	void SetTexture(const char * imagepath);
	void SetMaterial(Material* _material) override;
	void SetVerticesUV(float* vertices);
private:
	unsigned int texture;
	unsigned int verticesUV;
};

