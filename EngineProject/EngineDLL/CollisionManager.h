#pragma once
#include <map>
#include <list>
#include "Entity.h"
#include "Exports.h"

class ENGINEDLL_API CollisionManager
{
private:
	static CollisionManager* instance;
	std::map<std::string,list<Entity*>> colliderMap;
	CollisionManager();
public:
	static CollisionManager* GetInstance();
	void Update();
	void CheckCollisions();
	~CollisionManager();
	void AddToGroup(std::string groupName, Entity* collider);
};

