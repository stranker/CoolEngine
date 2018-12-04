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
	CheckBoxCollisions();
}
void CollisionManager::CheckBoxCollisions()
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
				if ((*iterA)->GetCollider()->isTrigger || (*iterB)->GetCollider()->isTrigger)
				{
					(*iterA)->OnCollision();
					(*iterB)->OnCollision();
				}
				else						
				{
					float pX = ((*iterA)->GetCollider()->width / 2 + (*iterB)->GetCollider()->width / 2) - modX;
					float pY = ((*iterA)->GetCollider()->height / 2 + (*iterB)->GetCollider()->height / 2) - modY;
					if (pX > pY)
					{
						//vertical
						if ((*iterA)->GetPos().y < (*iterB)->GetPos().y)
						{
							if((*iterA)->GetCollider()->isStatic)
								(*iterB)->MoveIn(0, pY, 0);
							else if((*iterB)->GetCollider()->isStatic)
								(*iterA)->MoveIn(0, -pY , 0);
							else
							{
								(*iterA)->MoveIn(0, -pY / 2, 0);
								(*iterB)->MoveIn(0, pY / 2, 0);
							}
						}
						else
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(0, -pY / 2, 0);
							else if ((*iterB)->GetCollider()->isStatic)
							(*iterA)->MoveIn(0, pY / 2, 0);
							else
							{
								(*iterA)->MoveIn(0, pY / 2, 0);
								(*iterB)->MoveIn(0, -pY / 2, 0);
							}
						}
					}
					else
					{
						//horizontal
						if ((*iterA)->GetPos().x < (*iterB)->GetPos().x)
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(pX / 2, 0, 0);
							else if ((*iterB)->GetCollider()->isStatic)
							(*iterA)->MoveIn(-pX / 2, 0, 0);
							else
							{
								(*iterA)->MoveIn(-pX / 2, 0, 0);
								(*iterB)->MoveIn(pX / 2, 0, 0);
							}
						}
						else
						{
							if ((*iterA)->GetCollider()->isStatic)
							(*iterB)->MoveIn(-pX / 2, 0, 0);
							else if ((*iterB)->GetCollider()->isStatic)								
							(*iterA)->MoveIn(pX / 2, 0, 0);
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
	}
}
void CollisionManager::CheckCircleCollisions()
{
	list<Shape*>::iterator iterA = colliderMap["C"].begin();
	list<Shape*>::iterator iterB = colliderMap["D"].begin();
	for (iterA; iterA != colliderMap["C"].end(); iterA++)
	{
		glm::vec3 diff;

		for (iterB; iterB != colliderMap["D"].end(); iterB++)
		{
			diff = (*iterB)->GetPos() - (*iterA)->GetPos();
			float modX = 0;
			float modY = 0;
			float distSqr;
			modX = std::abs(diff.x);
			modY = std::abs(diff.y);
			distSqr = modX * modX + modY * modY;			
		}
	}
}


