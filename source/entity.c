#include <stdlib.h>
#include "typedef.h"
#include "vector.h"
#include "entity.h"
#include "core.h"
#include "sprite.h"

Entity *newEntity(vec3 pos, vec3 scale, const char *sprite_name) {
	Entity *e = (Entity*)malloc(sizeof(Entity));
	
	e->pos = pos;
	e->scale = scale;
	
	if (sprite_name != NULL) {
		spriteLoad(&e->sprite, sprite_name);
	}
	
	Core *core = getGlobalCore();
	core->entities[core->entity_count] = e;
	++core->entity_count;
	
	return e;
}