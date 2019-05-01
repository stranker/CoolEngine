#include "Shape3D.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


Shape3D::Shape3D(Renderer* _renderer) :
	Entity(_renderer)
{
	float g_vertex_buffer_data[] = {		
		0,		0,		1.0,
		1.0,	0,		1.0,
		1.0,	1.0,	1.0,
		0,		1.0,	1.0,
		// back
		0,		0,		0,
		1.0,	0,		0,
		1.0,	1.0,	0,
		0,		1.0,	0
	};

	unsigned int g_index_buffer_data[] = {
		//front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};	
	float faceColors[] = 
	{
    // front colors
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    // back colors
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0
	};
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 8);
	SetIndexes(g_index_buffer_data, 36);	
	SetColorVertices(faceColors);
}
Shape3D::~Shape3D()
{
	Dispose();
}
void Shape3D::SetVertices(float* _vertices, int count)
{
	Dispose();
	vertices = _vertices;
	vtxCount = count;
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount * 3 * sizeof(float)));
}
void Shape3D::SetIndexes(unsigned int* _indexes, int count)
{	
	indexes = _indexes;	
	bufferIndex = (renderer->GenBufferIndex(indexes, count * sizeof(unsigned int) ));
}
void Shape3D::SetColorVertices(float* vertices)
{
	verticesColor = vertices;
	bufferColor = (renderer->GenBuffer(verticesColor, vtxCount * 3 * sizeof(float)));
}
void Shape3D::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());		
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(bufferData, 3, 0);
	renderer->BindBuffer(bufferColor, 3, 1);
	renderer->BindBufferIndex(bufferIndex);
	renderer->DrawIndex(vtxCount);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Shape3D::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		renderer->DeleteBuffers(bufferColor);
		/*if (vertices)
		{
		delete[] vertices;
		vertices = NULL;
		}*/
		shouldDispose = false;
	}
}
void Shape3D::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("SimpleVertexShader.txt", "SimpleFragmentShader.txt");
}
void Shape3D::BindMaterial()
{
	renderer->BindMaterial(programID);
}
void Shape3D::SetPosition(float x, float y, float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape3D::MoveIn(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Shape3D::SetScale(float x, float y, float z)
{
	scl[0] = x;
	scl[1] = y;
	scl[2] = z;

	scale = glm::scale(glm::mat4(1.0f), scl);
	UpdateModelMatrix();
}
void Shape3D::SetRotateX(float x)
{
	rot[0] = x;
	glm::vec3 axis;
	axis[0] = x;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModelMatrix();
}
void Shape3D::SetRotateY(float y)
{
	rot[1] = y;
	glm::vec3 axis;
	axis[1] = y;
	axis[0] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModelMatrix();
}
void Shape3D::SetRotateZ(float z)
{
	rot[2] = z;
	glm::vec3 axis;
	axis[2] = z;
	axis[0] = axis[1] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModelMatrix();
}
void Shape3D::UpdateModelMatrix()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}
