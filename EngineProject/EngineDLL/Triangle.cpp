#include "Triangle.h"

Triangle::Triangle(Renderer* _renderer) :
	Shape(_renderer)
{
	float g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triángulo 1 : termina
	};
	
	float g_color_buffer_data[] = {
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	};
	typeOfShape = Renderer::GL_TRIANGLES;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 3);
	SetColorVertices(g_color_buffer_data);
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
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(bufferData,3, 0);
	renderer->BindBuffer(bufferColor,3, 1);
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}