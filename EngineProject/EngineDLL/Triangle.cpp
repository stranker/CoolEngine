#include "Triangle.h"


Triangle::Triangle(Renderer* _renderer) :
	Entity(_renderer)
{	
	float* coord = new float[
		-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
	];
	SetVertices(coord, 3);
	Dispose();
}


Triangle::~Triangle()
{
	Dispose();
}
void Triangle::Draw()
{		
	renderer->DrawBuffer(bufferData, vtxCount);
}
void Triangle::SetVertices(float* _vertices, int count)
{	
	Dispose();
	vertices = _vertices;
	vtxCount = count;	
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount*3*sizeof(float)));
}
void Triangle::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);		
		if(vertices)
		delete[] vertices;
		shouldDispose = false;
	}
}
