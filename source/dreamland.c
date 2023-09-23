#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "input.h"
#include "sprite.h"
#include "vector.h"
#include "render.h"

#define PLAYER_SPEED   4.0f

global Core *core;
global Entity *player;
global Entity *ground;

global u32 ground_sprites[2];

global u32 background_sprite;

const u8 map[20 * 6] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void dreamlandEntry() {
	core = getGlobalCore();
	player = newEntity((vec3){0.0f, 0.0f, 0.0f},
										 (vec3){10.0f, 28.0f, 1.0f},
										 "sprites/player_idle_test.png",
										 PHYSICS_BODY_DYNAMIC);
	
	spriteLoad(&ground_sprites[0], "sprites/ground.png");
	spriteLoad(&ground_sprites[1], "sprites/ground_top.png");
	
	spriteLoad(&background_sprite, "sprites/background.png");
	
	for (u8 y = 0; y < 6; ++y) {
		for (u8 x = 0; x < 20; ++x) {
			u8 map_index = map[x + y * 20];
			
			if (map_index != 0) {
				newSimpleEntity((vec3){16.0f * x - 160.0f, 16.0f * -y, 0.0f},
												(vec3){16.0f, 16.0f, 1.0f},
												ground_sprites[map_index - 1],
												PHYSICS_BODY_STATIC);
			}
			continue;
		}
	}
}

void dreamlandUpdate() {
	player->vel.x = (inputKeyHeld('D') - inputKeyHeld('A')) * PLAYER_SPEED * 0.1f;
	player->vel.y = (inputKeyHeld('W') - inputKeyHeld('S')) * PLAYER_SPEED * 0.1f;
	
	renderDrawSprite(background_sprite, (vec3){0.0f, 0.0f, 0.0f}, (vec3){SCREEN_VIEW_WIDTH, SCREEN_VIEW_HEIGHT, 1.0f});
}