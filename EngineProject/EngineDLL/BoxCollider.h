#pragma once
#include "Exports.h"

class ENGINEDLL_API BoxCollider
{
public:
	float width;
	float height;
	bool isTrigger;
	bool isStatic;
	BoxCollider(float _width,float _height,bool _isTrigger,bool _isStatic);
	~BoxCollider();	
};

