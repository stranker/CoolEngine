#include "Rigidbody.h"

Rigidbody::Rigidbody(b2BodyType _bodyType, b2Vec2 _initialPos)
{
	bodyDef.type = _bodyType;
	bodyDef.angle = 0;
	pos = _initialPos;
}

Rigidbody::~Rigidbody()
{
}
