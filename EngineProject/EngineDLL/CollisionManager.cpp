#include "CollisionManager.h"
#include <glm\glm.hpp>
#include <math.h>
CollisionManager* CollisionManager::instance = 0;

CollisionManager* CollisionManager::GetInstance()
{
	if(instance == 0)
	{
		instance = new CollisionManager();		
	}
	return instance;
}

CollisionManager::CollisionManager()
{}
void CollisionManager::AddToGroup(std::string groupName, Entity* collider)
{
	colliderMap[groupName].push_back(collider);
}

void CollisionManager::Update()
{
	CheckCollisions();
}
void CollisionManager::CheckCollisions()
{
	list<Entity*>::iterator iterA = colliderMap["A"].begin();
	list<Entity*>::iterator iterB = colliderMap["B"].begin();
	for(iterA; iterA != colliderMap["A"].end();iterA++)
	{		
		glm::vec3 diff;

		for (iterB; iterB != colliderMap["B"].end(); iterB++)
		{
			diff = (*iterB)->GetPos() - (*iterA)->GetPos();
			float modX = std::abs(diff.x);
			float modY = std::abs(diff.y);
			if (modX < (*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2 &&
				modY < (*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2)
				std::cout << "dasdasd";
		}
	}
}

