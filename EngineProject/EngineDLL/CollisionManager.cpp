#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = 0;

CollisionManager* CollisionManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CollisionManager();
	}
	return instance;
}

void CollisionManager::AddToGroup(std::string groupName, Entity collider)
{

}
