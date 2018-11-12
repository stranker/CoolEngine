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
void CollisionManager::AddToGroup(std::string groupName, Shape* collider)
{
	colliderMap[groupName].push_back(collider);
}

void CollisionManager::Update()
{
	CheckCollisions();
}
void CollisionManager::CheckCollisions()
{
	list<Shape*>::iterator iterA = colliderMap["A"].begin();
	list<Shape*>::iterator iterB = colliderMap["B"].begin();
	for(iterA; iterA != colliderMap["A"].end();iterA++)
	{		
		glm::vec3 diff;

		for (iterB; iterB != colliderMap["B"].end(); iterB++)
		{
			diff = (*iterB)->GetPos() - (*iterA)->GetPos();
			float modX = 0;
			float modY = 0;
			modX = std::abs(diff.x);
			modY = std::abs(diff.y);
			if (modX < (*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2 &&
				modY < (*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2)
			{
				float pX = ((*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2) - modX;
				float pY = ((*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2) - modY;
				if (pX > pY)
				{
					//vertical
					if ((*iterA)->GetPos().y < (*iterB)->GetPos().y)
					{			
						(*iterA)->MoveIn(0,-pY / 2, 0);
						(*iterB)->MoveIn(0,pY / 2,0);
					}
					else
					{
						(*iterA)->MoveIn(0,pY / 2, 0);
						(*iterB)->MoveIn(0,-pY / 2, 0);
					}
				}
				else
				{
					if ((*iterA)->GetPos().x < (*iterB)->GetPos().x)
					{
						(*iterA)->MoveIn(-pX / 2, 0, 0);
						(*iterB)->MoveIn(pX / 2, 0, 0);
					}
					else
					{
						(*iterA)->MoveIn(pX / 2, 0, 0);
						(*iterB)->MoveIn(-pX / 2, 0, 0);
					}
				}
			}
		}
	}
}

