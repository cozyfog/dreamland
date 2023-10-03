#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "input.h"
#include "sprite.h"
#include "vector.h"
#include "render.h"
#include "sound.h"

#define PLAYER_SPEED   1.0f

global Core *core;
global Entity *player;
global Entity *ground;

global u32 ground_sprites[2];

global Sound *sound_ambience;
global Sound *sound_footstep;

const u8 map[20 * 12] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
	2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void dreamlandEntry() {
	core = getGlobalCore();
	player = newEntity((vec3){0.0f, 0.0f, 0.0f},
										 (vec3){10.0f, 28.0f, 1.0f},
										 "sprites/player_idle_test.png",
										 (PhysicsBody){
											 PHYSICS_BODY_DYNAMIC,
											 (vec2){0.0f, 0.0f},
											 (vec2){8.0f, 28.0f}
										 });
	
	spriteLoad(&ground_sprites[0], "sprites/ground.png");
	spriteLoad(&ground_sprites[1], "sprites/ground_top.png");
	
	sound_ambience = soundLoad("sounds/ambience.wav");
	sound_footstep = soundLoad("sounds/footstep.wav");
	
	soundSetVolume(sound_ambience, 0.6f);
	soundSetVolume(sound_footstep, 1.0f);
	
	for (u8 y = 0; y < 12; ++y) {
		for (u8 x = 0; x < 20; ++x) {
			u8 map_index = map[x + y * 20];
			
			if (map_index != 0) {
				newSimpleEntity((vec3){16.0f * x - 160.0f, 16.0f * -y + 96, 0.0f},
												(vec3){16.0f, 16.0f, 1.0f},
												ground_sprites[map_index - 1],
												(PhysicsBody){
													PHYSICS_BODY_STATIC,
													(vec2){0.0f, 0.0f},
													(vec2){16.0f, 16.0f}
												});
			}
			continue;
		}
	}
}

void dreamlandUpdate() {
	soundPlay(sound_ambience);
	
	player->vel.x = (inputKeyHeld('D') - inputKeyHeld('A')) * PLAYER_SPEED * 0.1f;
	player->vel.y = (inputKeyHeld('W') - inputKeyHeld('S')) * PLAYER_SPEED * 0.1f;
	
	if (player->vel.x == 0.0f) {
		if (soundPlaying(sound_footstep)) {
			soundStop(sound_footstep);
		}
	} else {
		soundPlay(sound_footstep);
	}
}