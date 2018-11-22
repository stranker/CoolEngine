#pragma once
#include "Renderer.h"|
#include "Material.h"
#include "Exports.h"
#include <vector>
using namespace std;
class ENGINEDLL_API Tilemap
{
private:
	int screenHeight;
	int screenWidth;
	Renderer* renderer;

	glm::mat4 model;
	void Dispose();
	void BindMaterial();
	int heightTile;
	int widthTile;
	int heightTextureTotal;
	int widthTextureTotal;
	int tileTotalPerRow;	
	vector<float> vertexArrayPos;
	vector<float> vertexArrayUV;
	vector<int> tilesWithCollides;
	struct tilemapData
	{
		int tilesPerRow;
		int tilesPerCol;
		int tileHeight;
		int tileWidth;
		vector<int> tiles;
	};
	tilemapData tilesData;	
	void SetVertices(float* _vertices, int count);	
public:	
	Tilemap(Renderer* _renderer,int _screenHeight,int _screenWidth);
	~Tilemap();
	unsigned int texture;
	unsigned int verticesUV;
	Material * material;
	unsigned int bufferData;
	unsigned int bufferColor;
	unsigned int programID;
	float* vertices;
	float* verticesColor;
	bool shouldDispose;
	int vtxCount;
	int vtxSize;
	void Draw();
	void SetTexture(const char * imagepath);
	void SetVerticesUV(float* vertices);	
	void SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow);
	void SetMaterial(Material* _material);
	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);	
	bool degenerateTriangle = false;
	void SetColliderTiles(vector<int> v);
};

