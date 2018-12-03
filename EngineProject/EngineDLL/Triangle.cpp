#include "Triangle.h"

Triangle::Triangle(Renderer* _renderer) :
	Shape(_renderer)
{
	float g_vertex_buffer_data[] = {
		0.0f,0.0f,1.0f,
		1.0f,0.0f,1.0f,
		0.5f,1.0f,1.0f,
	};
	
	float g_color_buffer_data[] = {
		0.5f,  1.0f,  0.3f,
		1.0f,  1.0f,  1.0f,
		0.3f,  1.0f,  0.5f,
	};
	typeOfShape = Renderer::RGL_TRIANGLES;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 3);
	SetColorVertices(g_color_buffer_data);
	SetScale(64, 64, 1);
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