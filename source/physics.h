/* date = September 23rd 2023 9:25 am */

#ifndef PHYSICS_H
#define PHYSICS_H

#include "typedef.h"
#include "vector.h"

enum(PhysicsBodyType) {
	PHYSICS_BODY_STATIC,
	PHYSICS_BODY_DYNAMIC
};

class(PhysicsBody) {
	PhysicsBodyType type;
	vec2 offset;
	vec2 scale;
};

void physicsEntry();
void physicsUpdate();

#endif //PHYSICS_H
