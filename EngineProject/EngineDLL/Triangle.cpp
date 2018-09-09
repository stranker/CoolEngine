#include "Triangle.h"


Triangle::Triangle(Renderer* _renderer) :
	Entity(_renderer)
{
	bufferData = -1;
	vertices = 0;
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
	bufferData = (renderer->GenBuffer(vertices, vtxCount));
	shouldDispose = true;
}
void Triangle::Dispose()
{
	if (shouldDispose)
	{
		//glDeleteBuffers(1, (GLuint*)bufferData);
		delete[] vertices;
		shouldDispose = false;
	}
}
