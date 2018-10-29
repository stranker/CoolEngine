#pragma once
#include <map>
#include "Entity.h"
class CollisionManager
{
private:
	static CollisionManager * instance;
	std::map<std::string,Entity> colliderMap;
	CollisionManager();
public:
	static CollisionManager* GetInstance();
	~CollisionManager();
	void AddToGroup(std::string groupName, Entity collider);
};

