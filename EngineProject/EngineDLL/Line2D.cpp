#include "Line2D.h"


Line2D::Line2D(Renderer* rend) : Shape(rend)
{
	float g_vertex_buffer_data[] = {
		0.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
	};

	float g_uv_buffer_data[] = {
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f
	};
	typeOfShape = Renderer::RGL_LINE_STRIP;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 4);
	pivot.x = 0;
	pivot.y = 0;
	pivot.z = 0;
}


Line2D::~Line2D()
{
	Dispose();
}

void Line2D::Draw()
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
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}

void Line2D::SetMaterial(Material * _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
