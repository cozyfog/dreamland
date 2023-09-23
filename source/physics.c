#include "typedef.h"
#include "physics.h"
#include "core.h"
#include "cute_c2.h"
#include "vector.h"
#include "entity.h"

global Core *core;

void physicsEntry() {
	core = getGlobalCore();
}

internal void physicsResponse(Entity *entity, Entity *other) {
	bool on_top = entity->pos.y > other->pos.y;
	bool on_right = entity->pos.x > other->pos.x;
	
	// TODO
}

void physicsUpdate() {
	u64 curr_index = 0;
	Entity *curr = core->entities[curr_index];
	
	while (curr != NULL || curr_index < core->entity_count) {
		curr->last = curr->pos;
		curr->pos = vec3_add_vec3(curr->pos, curr->vel);
		
		if (curr->physics_body == PHYSICS_BODY_STATIC) {
			curr = core->entities[++curr_index];
			continue;
		}
		
		vec3 curr_half = vec3_mul(curr->scale, 0.5);
		c2AABB curr_aabb = {
			vec3_to_c2v(vec3_sub_vec3(curr->pos, curr_half)),
			vec3_to_c2v(vec3_add_vec3(curr->pos, curr_half))
		};
		
		u64 coll_index = 0;
		Entity *coll = core->entities[coll_index];
		while (coll != NULL || coll_index < core->entity_count) {
			if (coll_index == curr_index) {
				coll = core->entities[++coll_index];
				continue;
			}
			
			vec3 coll_half = vec3_mul(coll->scale, 0.5);
			c2AABB coll_aabb = {
				vec3_to_c2v(vec3_sub_vec3(coll->pos, coll_half)),
				vec3_to_c2v(vec3_add_vec3(coll->pos, coll_half))
			};
			
			if (c2AABBtoAABB(curr_aabb, coll_aabb)) {
				physicsResponse(curr, coll);
			}
			
			coll = core->entities[++coll_index];
		}
		
		curr = core->entities[++curr_index];
	}
}