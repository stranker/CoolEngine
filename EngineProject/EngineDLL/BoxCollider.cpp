#include "BoxCollider.h"



BoxCollider::BoxCollider(float _width, float _height, bool _isTrigger, bool _isStatic)
	: width(_width), height(_height), isTrigger(_isTrigger), isStatic(_isStatic)
{
}


BoxCollider::~BoxCollider()
{
}
