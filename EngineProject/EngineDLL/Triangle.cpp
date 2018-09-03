#include "Triangle.h"


Triangle::Triangle(Material* _material,Renderer* _renderer) : 
	material(_material),
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
}
void Triangle::SetVertices(float* _vertices, int count)
{	
	Dispose();
	vertices = _vertices;
	vtxCount = count;
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
