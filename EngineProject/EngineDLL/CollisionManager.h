#pragma once
#include <map>
#include <list>
#include "Shape.h"
#include "Exports.h"

class ENGINEDLL_API CollisionManager
{
private:
	static CollisionManager* instance;
	std::map<std::string,list<Shape*>> colliderMap;
	CollisionManager();
public:
	static CollisionManager* GetInstance();
	void Update();
	void CheckBoxCollisions();
	~CollisionManager();
	void AddToGroup(std::string groupName, Shape* collider);
	void CheckCircleCollisions();
};

