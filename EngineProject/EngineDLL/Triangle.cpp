#include "Triangle.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}
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
void Triangle::SetPosition(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Triangle::SetScale(float x, float y, float z)
{
	scl[0] = x;
	scl[1] = y;
	scl[2] = z;

	scale = glm::scale(glm::mat4(1.0f), scl);
	UpdateModelMatrix();
}
void Triangle::SetRotateX(float x)
{
	rot[0] = x;
	glm::vec3 axis;
	axis[0] = x;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModelMatrix();
}
void Triangle::SetRotateY(float y)
{
	rot[1] = y;
	glm::vec3 axis;
	axis[0] = y;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f),y, axis);
	UpdateModelMatrix();
}
void Triangle::SetRotateZ(float z)
{
	rot[2] = z;
	glm::vec3 axis;
	axis[0] = z;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModelMatrix();
}
void Triangle::UpdateModelMatrix()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}
