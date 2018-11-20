#include "Tilemap.h"
#include "TextureImporter.h"
#include <vector>
#include "GL\glew.h"
Tilemap::Tilemap(Renderer* _renderer, int _screenHeight, int _screenWidth) :
	renderer(_renderer) , screenHeight(_screenHeight), screenWidth(_screenWidth)
{
	model = glm::mat4(1.0f);
	float g_uv_buffer_data[] = {
		0.0f,1.0f,
		0.0f,0.0f,
		1.0f,1.0f,
		1.0f,0.0f
	};	

	shouldDispose = false;	
	tileTotalPerRow = 0;
}
Tilemap::~Tilemap()
{
}

void Tilemap::SetMaterial(Material* _material)
{
	material = _material;
	programID = material->LoadShaders("TextureVertexShader.txt", "TextureFragmentShader.txt");
}
void Tilemap::SetTexture(const char * imagepath)
{
	texture = TextureImporter::loadBMP_custom(imagepath);
	heightTile = 64;
	widthTile = 64;
	heightTotal = TextureImporter::dataStruct.height;
	widthTotal = TextureImporter::dataStruct.width;		

	
	indexes = {
		{4,4},{4,4}
	};

	for (int i = 0; i < indexes.size(); i++)
	{		
		for (int j = 0; j < indexes[0].size(); j++)
		{
			vertexArrayPos.push_back(0.0f + j);
			vertexArrayPos.push_back(1.0f - i);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(1.0f + j);
			vertexArrayPos.push_back(1.0f - i);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(0.0f + j);
			vertexArrayPos.push_back(0.0f - i);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(1.0f + j);
			vertexArrayPos.push_back(0.0f - i);
			vertexArrayPos.push_back(0.0f);

			if (j == indexes[0].size() -1)
			{
				vertexArrayPos.push_back(1.0f + j);
				vertexArrayPos.push_back(0.0f - i);
				vertexArrayPos.push_back(0.0f);

				vertexArrayPos.push_back(0.0f);
				vertexArrayPos.push_back(1.0f - i-1);
				vertexArrayPos.push_back(0.0f);
			}
		}
	}
	float* p = &vertexArrayPos[0];
	SetVertices(p, 4*indexes.size()*indexes[0].size() + 2*(indexes.size()-1));

	for (int i = 0; i < indexes.size(); i++)
		for (int j = 0; j < indexes[0].size(); j++)
		{
			int id = indexes[i][j];
			vertexArrayUV.push_back(GetOffsetX(id) / widthTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) / heightTotal));

			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTotal);
			vertexArrayUV.push_back(1 - GetOffsetY(id) / heightTotal);

			vertexArrayUV.push_back(GetOffsetX(id) / widthTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTotal);

			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTotal);
		}
	p = &vertexArrayUV[0];
	SetVerticesUV(p);
}

void Tilemap::Draw()
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
	renderer->BindBuffer(bufferData, 3, 0);
	renderer->BindBuffer(verticesUV, 2, 1);
	renderer->Draw(vtxCount, Renderer::RGL_TRIANGLE_STRIP);
	renderer->DisableBuffer(0);
	renderer->DisableBuffer(1);
}
void Tilemap::SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow)
{
	widthTile = frameWidth;
	heightTile = frameHeight;
	tileTotalPerRow = framesCountPerRow;	
}
float Tilemap::GetOffsetX(unsigned int id)
{
	return (id % tileTotalPerRow)*widthTile;
}
float Tilemap::GetOffsetY(unsigned int id)
{
	return (id / tileTotalPerRow)*heightTile;
}
void Tilemap::BindMaterial()
{
	renderer->BindMaterial(programID);
}
void Tilemap::SetVertices(float* _vertices, int count)
{
	Dispose();
	vertices = _vertices;
	vtxCount = count;
	shouldDispose = true;
	bufferData = (renderer->GenBuffer(vertices, vtxCount * 3 * sizeof(float)));
}
void Tilemap::SetVerticesUV(float* vertices)
{
	verticesUV = (renderer->GenBuffer(vertices, vtxCount * 2 * sizeof(float)));
}
void Tilemap::Dispose()
{
	if (shouldDispose)
	{
		renderer->DeleteBuffers(bufferData);
		renderer->DeleteBuffers(bufferColor);
		if (vertices)
		{
			delete[] vertices;
			vertices = NULL;
		}
		shouldDispose = false;
	}
}
