#include "Triangle.h"


Triangle::Triangle(Renderer* _renderer) :
	Entity(_renderer)
{
	float* coord = new float[9] {
		-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
	};

	shouldDispose = false;
	SetVertices(coord, 3);	
}


Triangle::~Triangle()
{
	Dispose();
}
void Triangle::Draw()
{
	if (material)
		BindMaterial();
	renderer->DrawBuffer(bufferData, vtxCount);
}
void Triangle::SetVertices(float* _vertices, int count)
{
	Dispose();
	vertices = _vertices;
	vtxCount = count;
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount * 3 * sizeof(float)));
}
void Triangle::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		if (vertices)
		{
			delete[] vertices;
			vertices = NULL;
		}
		shouldDispose = false;
	}
}
void Triangle::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}
void Triangle::BindMaterial()
{
	renderer->BindMaterial(programID);
}
