/* date = September 23rd 2023 9:25 am */

#ifndef PHYSICS_H
#define PHYSICS_H

#include "typedef.h"

enum(PhysicsBody) {
	PHYSICS_BODY_STATIC,
	PHYSICS_BODY_DYNAMIC
};

void physicsEntry();
void physicsUpdate();

#endif //PHYSICS_H
