/* date = August 14th 2023 2:19 pm */

#ifndef ENTITY_H
#define ENTITY_H

#include "typedef.h"
#include "vector.h"
#include "physics.h"

#define MAX_ENTITY_COUNT       512

class(Entity) {
	vec3 pos;
	vec3 scale;
	vec3 vel;
	vec3 last;
	PhysicsBody physics_body;
	u32 sprite;
};

Entity *newSimpleEntity(vec3 pos, vec3 scale, u32 sprite, PhysicsBody physics_body);
Entity *newEntity(vec3 pos, vec3 scale, const char *sprite_name, PhysicsBody physics_body);

#endif //ENTITY_H
