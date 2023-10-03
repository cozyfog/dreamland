#include "typedef.h"
#include "physics.h"
#include "core.h"
#include "vector.h"
#include "entity.h"

global Core *core;

void physicsEntry() {
	core = getGlobalCore();
}

bool AABBvsAABB(Entity *a, Entity *b) {
	vec2 a_min = {a->pos.x + a->physics_body.offset.x, a->pos.y + a->physics_body.offset.y};
	vec2 a_max = vec2_add_vec2(a_min, a->physics_body.scale);
	
	vec2 b_min = {b->pos.x + b->physics_body.offset.x, b->pos.y + b->physics_body.offset.y};
	vec2 b_max = vec2_add_vec2(b_min, b->physics_body.scale);
	
  if(a_max.x < b_min.x || a_min.x > b_max.x) return false;
	if(a_max.y < b_min.y || a_min.y > b_max.y) return false;
	return true;
}

void physicsUpdate() {
	for (u64 i = 0; i < core->entity_count; ++i) {
		Entity *entity = core->entities[i];
		
		if (entity->physics_body.type == PHYSICS_BODY_STATIC) {
			continue;
		}
		
		entity->pos = vec3_add_vec3(entity->pos, entity->vel);
		/*
		Entity hits[MAX_ENTITY_COUNT] = {0};
		u64 hit_index = 0;
		for (u64 j = 0; j < core->entity_count; ++j) {
			if (j == i) continue;
			
			Entity *other = core->entities[j];
			
			if (AABBvsAABB(entity->aabb, other->aabb)) {
				hits[hit_index] = other;
				++hit_index;
			}
		}*/
	}
}