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
	screenHeight(_screenHeight), screenWidth(_screenWidth), Shape(_renderer)
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
			int col =  j* widthTile;			
			int row =  i *heightTile;

											   
			vertexArrayPos.push_back(0.0f + col);
			vertexArrayPos.push_back(-heightTile - row);
			vertexArrayPos.push_back(0.0f);	   

			vertexArrayPos.push_back(widthTile + col);
			vertexArrayPos.push_back(-heightTile - row);
			vertexArrayPos.push_back(0.0f);	   

											   											   
			vertexArrayPos.push_back(widthTile + col);
			vertexArrayPos.push_back(0.0f - row);
			vertexArrayPos.push_back(0.0f);

			vertexArrayPos.push_back(0.0f + col);
			vertexArrayPos.push_back(0.0f - row);
			vertexArrayPos.push_back(0.0f);	   
		}
	}
	float* p = &vertexArrayPos[0];
	SetVertices(p, 4 * indexes.size()*indexes[0].size());

	for (int i = 0; i < indexes.size(); i++)
		for (int j = 0; j < indexes[0].size(); j++)
		{
			int id = indexes[i][j];

			//00
			vertexArrayUV.push_back(GetOffsetX(id) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTextureTotal);
			//10
			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) + heightTile) / heightTextureTotal);
			//11
			vertexArrayUV.push_back((GetOffsetX(id) + widthTile) / widthTextureTotal);
			vertexArrayUV.push_back(1 - GetOffsetY(id) / heightTextureTotal);
			//01
			vertexArrayUV.push_back(GetOffsetX(id) / widthTextureTotal);
			vertexArrayUV.push_back(1 - (GetOffsetY(id) / heightTextureTotal));
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
void Tilemap::SetVerticesUV(float* vertices)
{
	verticesUV = (renderer->GenBuffer(vertices, vtxCount * 2 * sizeof(float)));
}
bool Tilemap::NextTileIsCollider(float x, float y)
{
	int tileID;

	x = (x - GetPos().x);
	y = -(y + GetPos().y);

	if (x >= 0 && y >= 0)
	{
		int col = x / widthTile;
		int row = y / heightTile;

		std::cout << "x: " << x << " - y: " << y << " - col: " << col << " - row: " << row << endl;

		int temp = indexes.size();
		if (col >= 0 && col < indexes[0].size() && row >= 0 && row < temp)
		{			
			tileID = indexes[row][col];
			for (vector<int>::iterator it = tilesWithCollides.begin(); it < tilesWithCollides.end(); it++)
			{
				if (*it == tileID)
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Tilemap::SetColliderTiles(vector<int> v)
{
	tilesWithCollides = v;
}
float Tilemap::GetTileX(float x)
{
	int col = (x - GetPos().x) / widthTile;
	return col * widthTile + GetPos().x;
}
float Tilemap::GetTileY(float y)
{
	int row = (y + GetPos().y) / heightTile;

	return row * heightTile - GetPos().y;
}
