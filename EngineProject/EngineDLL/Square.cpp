#include "Square.h"



Square::Square(Renderer* _renderer) :
	Shape(_renderer)
{
	float g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-2.0f,2.0f,2.0f
	};

	float g_color_buffer_data[] = {
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f
	};
	typeOfShape = Renderer::GL_TRIANGLE_STRIP;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 4);
	SetColorVertices(g_color_buffer_data);
}


Square::~Square()
{
	Dispose();
}
void Square::Draw()
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
	renderer->BindBuffer(bufferData,0);
	renderer->BindBuffer(bufferColor, 1);
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
