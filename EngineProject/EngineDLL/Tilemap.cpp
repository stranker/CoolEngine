#include "Tilemap.h"
#include "TextureImporter.h"
#include <vector>
#include "GL\glew.h"
#include "json.hpp"
#include <fstream>
#include <vector>
#include <math.h>

Tilemap* Tilemap::instance = 0;

Tilemap* Tilemap::GetInstance()
{
	return instance;
}



using json = nlohmann::json;
using namespace std;

Tilemap::Tilemap(Renderer* _renderer, int _screenHeight, int _screenWidth) :
	renderer(_renderer), screenHeight(_screenHeight), screenWidth(_screenWidth)
{


	std::ifstream istream("tilemap.json");
	json j;
	j = json::parse(istream);
	tilesData.tileHeight = j["tileheight"];
	tilesData.tileWidth = j["tilewidth"];
	tilesData.tilesPerRow = j["width"];
	tilesData.tilesPerCol = j["height"];
	vector<int> vec = j["layers"][0]["data"];
	tilesData.tiles = vec;
	instance = this;
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
	heightTile = tilesData.tileHeight;
	widthTile = tilesData.tileWidth;
	heightTextureTotal = TextureImporter::dataStruct.height;
	widthTextureTotal = TextureImporter::dataStruct.width;
	indexes = vector<vector<int>>(tilesData.tilesPerCol, vector<int>(tilesData.tilesPerRow));
	int conta = 0;
	for (int i = 0; i < indexes.size(); i++)
	{
		for (int j = 0; j < indexes[0].size(); j++)
		{
			if (tilesData.tiles[conta] == 0)
				indexes[i][j] = 11;
			else
				indexes[i][j] = tilesData.tiles[conta] - 1;
			conta++;
		}
	}
	for (int i = 0; i < indexes.size(); i++)
	{
		for (int j = 0; j < indexes[0].size(); j++)
		{
			vertexArrayPos.push_back(0.0f + j);
			vertexArrayPos.push_back(0.0f - i);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(0.0f + j);
			vertexArrayPos.push_back(1.0f - i);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(1.0f + j);
			vertexArrayPos.push_back(1.0f - i);
			vertexArrayPos.push_back(0.0f);


			vertexArrayPos.push_back(1.0f + j);
			vertexArrayPos.push_back(0.0f - i);
			vertexArrayPos.push_back(0.0f);
		}
	}
	float* p = &vertexArrayPos[0];
	SetVertices(p, 4 * indexes.size()*indexes[0].size() + 2 * (indexes.size() - 1));

	for (int i = 0; i < indexes.size(); i++)
		for (int j = 0; j < indexes[0].size(); j++)
		{
			int id = indexes[i][j];

			//00
			vertexArrayUV.push_back(GetOffsetX(id) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTextureTotal);
			//01
			vertexArrayUV.push_back(GetOffsetX(id) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) / heightTextureTotal));
			//11
			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTextureTotal);
			vertexArrayUV.push_back(1 - GetOffsetY(id) / heightTextureTotal);
			//10
			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTextureTotal);
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
	renderer->Draw(vtxCount, Renderer::RGL_QUADS);
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
bool Tilemap::GetTile(float x, float y)
{
	bool isCollider = false;
	if (y > 0 || y < -tilesData.tilesPerCol || x < 0 || x > tilesData.tilesPerRow)
		return isCollider;
	y = abs(y);

	int tileID;
	if (x != 0)
		x = round(x / (tilesData.tileWidth));
	if (y != 0)
		y = round(y / (tilesData.tileHeight));
	tileID = indexes[x][y];
	for (vector<int>::iterator it = tilesWithCollides.begin(); it < tilesWithCollides.end(); it++)
	{
		if (*it == tileID)
			isCollider = true;
	}

	return isCollider;
}
void Tilemap::SetColliderTiles(vector<int> v)
{
	tilesWithCollides = v;
}
