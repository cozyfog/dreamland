/* date = August 14th 2023 2:19 pm */

#ifndef ENTITY_H
#define ENTITY_H

#include "typedef.h"
#include "vector.h"
#include "sprite.h"

#define MAX_ENTITY_COUNT       512

typedef struct {
	vec3 pos;
	vec3 scale;
	vec3 vel;
	u32 sprite;
} Entity;

Entity *newEntity(vec3 pos, vec3 scale, const char *sprite_name);

#endif //ENTITY_H
