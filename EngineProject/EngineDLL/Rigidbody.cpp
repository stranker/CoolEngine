#include "Rigidbody.h"

Rigidbody::Rigidbody(b2BodyType _bodyType)
{
	bodyDef.type = _bodyType;
	bodyDef.angle = 0;
}

Rigidbody::~Rigidbody()
{
}
