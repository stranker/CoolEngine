#pragma once
#include "Renderer.h"|
#include "Material.h"
#include "Exports.h"
#include <vector>
#include "Player.h"
using namespace std;
class ENGINEDLL_API Tilemap : public Shape
{
private:
	static Tilemap* instance;
	unsigned int texture;
	int screenHeight;
	int screenWidth;				
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
public:		
	static Tilemap* GetInstance();
	Tilemap(Renderer* _renderer,int _screenHeight,int _screenWidth);
	~Tilemap();	
	unsigned int verticesUV;									
	void Draw() override;
	void SetTexture(const char * imagepath);
	void SetMaterial(Material* _material) override;
	void SetVerticesUV(float* vertices);	
	void SetFrameType(int frameWidth, int frameHeight, int framesCountPerRow);	
	float GetOffsetX(unsigned int id);
	float GetOffsetY(unsigned int id);		
	void SetColliderTiles(vector<int> v);
	bool NextTileIsCollider(float x, float y);
	vector<vector<int>> indexes;			
	float GetTileX(float x);
	float GetTileY(float y);
	void OnCollision() override {};
	void OnUpdate(float deltaTime) override {};
};

