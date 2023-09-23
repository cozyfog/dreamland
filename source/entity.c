#include <stdlib.h>
#include "typedef.h"
#include "vector.h"
#include "entity.h"
#include "core.h"
#include "sprite.h"
#include "physics.h"

Entity *newSimpleEntity(vec3 pos, vec3 scale, u32 sprite, PhysicsBody physics_body) {
	Entity *e = (Entity*)malloc(sizeof(Entity));
	
	e->pos = pos;
	e->last = e->pos;
	e->scale = scale;
	e->sprite = sprite;
	e->vel = (vec3){0.0f, 0.0f, 0.0f}; // NOTE(Daniel): Needs to be set due to malloc filling is with junk data.
	e->physics_body = physics_body;
	
	Core *core = getGlobalCore();
	core->entities[core->entity_count] = e;
	++core->entity_count;
	
	return e;
}

Entity *newEntity(vec3 pos, vec3 scale, const char *sprite_name, PhysicsBody physics_body) {
	Entity *e = newSimpleEntity(pos, scale, 0, physics_body);
	
	if (sprite_name != NULL) {
		spriteLoad(&e->sprite, sprite_name);
	}
	
	return e;
}
