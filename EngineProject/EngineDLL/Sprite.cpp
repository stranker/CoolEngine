#include "Sprite.h"
#include "TextureImporter.h"


Sprite::Sprite(Renderer* _renderer) :
	Shape(_renderer)
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
	typeOfShape = Renderer::RGL_TRIANGLE_STRIP;
	shouldDispose = false;
	SetVertices(g_vertex_buffer_data, 4);
	SetVerticesUV(g_uv_buffer_data);
}
void Sprite::SetVerticesUV(float* vertices)
{
	verticesUV = (renderer->GenBuffer(vertices, vtxCount * 2 * sizeof(float)));
}
Sprite::~Sprite()
{
	Dispose();
}
void Sprite::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Sprite::SetTexture(const char * imagepath)
{
	texture = TextureImporter::loadBMP_custom(imagepath);
	heightFrame = 64;
	widthFrame = 64;
	heightTotal = TextureImporter::dataStruct.height;
	widthTotal = TextureImporter::dataStruct.width;

	float g_vertex_buffer_data[] = {
		0.0f,heightFrame,0.0f,
		widthFrame,heightFrame,0.0f,
		0.0f,0.0f,0.0f,
		widthFrame,0.0f,0.0f,
	};	
	SetVertices(g_vertex_buffer_data, 4);
}

void Sprite::Draw()
{
	renderer->LoadIdentityMatrix();
	renderer->MultiplyModelMatrix(model);
	if (material)
	{
		BindMaterial();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
		material->SetTextureProperty("myTextureSampler", texture);
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(bufferData,3, 0);
	renderer->BindBuffer(verticesUV,2,1);
	renderer->Draw(vtxCount, typeOfShape);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Sprite::SetFrame(unsigned int id)
{
	float vertices[] =
	{
		GetOffsetX(id) / widthTotal, 1 - (GetOffsetY(id) / heightTotal) ,
		(GetOffsetX(id) + widthFrame) / widthTotal, 1 - GetOffsetY(id) / heightTotal,
		GetOffsetX(id) / widthTotal, 1 - ( GetOffsetY(id) + heightFrame) / heightTotal,
		(GetOffsetX(id) + widthFrame) / widthTotal, 1 - (GetOffsetY(id) + heightFrame) / heightTotal		
	};
	SetVerticesUV(vertices);
}
void Sprite::SetFrameType(int frameWidth,int frameHeight,int framesCountPerRow)
{
	widthFrame = frameWidth;
	heightFrame = frameHeight;
	framesTotal = framesCountPerRow;
}
float Sprite::GetOffsetX(unsigned int id)
{
	return (id % framesTotal)*widthFrame;
}
float Sprite::GetOffsetY(unsigned int id)
{
	return (id/ framesTotal)*heightFrame;
}