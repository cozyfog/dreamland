#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "input.h"
#include "cute_c2.h"

#define PLAYER_SPEED   4.0f

global Core *core;
global Entity *player;
global Entity *ground;

void dreamlandEntry() {
	core = getGlobalCore();
	player = newEntity((vec3){0.0f, 15.0f, 0.0f}, (vec3){28.0f, 28.0f, 1.0f}, "sprites/player_idle_test.png");
	ground = newEntity((vec3){0.0f, -32.0f, 0.0f}, (vec3){100.0f, 10.0f, 1.0f}, "sprites/debug.png");
}

void dreamlandUpdate() {
	player->vel.x = (inputKeyHeld('D') - inputKeyHeld('A')) * PLAYER_SPEED * 0.1f;
	player->vel.y = (inputKeyHeld('W') - inputKeyHeld('S')) * PLAYER_SPEED * 0.1f;
	
	vec3 ps = {player->scale.x * 0.5f, player->scale.y * 0.5f};
	vec3 gs = {ground->scale.x * 0.5f, ground->scale.y * 0.5f};
	
	c2AABB player_aabb = {vec3_to_c2v(vec3_sub_vec3(player->pos, ps)), vec3_to_c2v(vec3_add_vec3(player->pos, ps))};
	c2AABB ground_aabb = {vec3_to_c2v(vec3_sub_vec3(ground->pos, gs)), vec3_to_c2v(vec3_add_vec3(ground->pos, gs))};
	
	if (c2AABBtoAABB(player_aabb, ground_aabb)) {
		puts("true");
	} else {
		puts("false");
	}
}