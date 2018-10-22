#include "Circle.h"
#include <math.h>


Circle::Circle(Renderer* _renderer) :
	Shape(_renderer)
{
	float g_color_buffer_data[] = {
		1.0f,  1.0f,  1.0f,
		0.13f,  1.0f,  1.0f,
		1.0f,  1.0f,  0.23f,
		1.0f,  1.0f,  1.0f,
		0.13f,  1.0f,  1.0f,
		1.0f,  1.0f,  0.23f,
		1.0f,  1.0f,  1.0f,
		0.13f,  1.0f,  1.0f,
		1.0f,  1.0f,  0.23f,
		1.0f,  0.55f,  1.0f,
	};

	vtxCount = 10;
	radius = 2.0f;
	typeOfShape = Renderer::GL_TRIANGLE_FAN;
	shouldDispose = false;
	vertexSeparationInDegrees = 360/vtxCount;
	CalculateCircleVertex();
	SetColorVertices(g_color_buffer_data);
}

void Circle::CalculateCircleVertex()
{
	float vertexInCircle[10*3];
	int currentIndex;
	float angle = 0;
	for (int i = 0; i < vtxCount; i++)
	{
		currentIndex = i * 3;
		vertexInCircle[currentIndex] = cos(angle) * radius;
		vertexInCircle[currentIndex+1] = sin(angle)*radius;
		vertexInCircle[currentIndex + 2] = 0.0f;	
		angle += vertexSeparationInDegrees * 3.1415f / 180.0f;
	}
	SetVertices(vertexInCircle,vtxCount);
}
Circle::~Circle()
{
	Dispose();
}
void Circle::Draw()
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
