#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "input.h"

#define PLAYER_MAX_SPEED   2
#define PLAYER_ACCEL       0.4f
#define PLAYER_DECEL       0.2f

global Core *core;
global Entity *player;

void dreamlandEntry() {
	core = getGlobalCore();
	player = newEntity((vec3){0.0f, 15.0f, 0.0f}, (vec3){28.0f, 28.0f, 1.0f}, "sprites/player_idle_test.tff");
}

void dreamlandUpdate() {
	if (player->pos.y <= -45) {
		player->pos.y = -45.0f;
	} else {
		player->vel.y -= 0.2f * core->time.dt;
	}
	
	// NOTE(daniel): Keep both so I don't have to add checks for stuff like wen 'A' && 'D'.
	//               It theoratically cancels itself out.
	
	if (inputKeyHeld('D') && player->vel.x < PLAYER_MAX_SPEED) {
		player->vel.x += PLAYER_ACCEL * core->time.dt;
	} else {
		if (player->vel.x > 0.0f) {
			player->vel.x -= PLAYER_DECEL * core->time.dt;
			if (player->vel.x <= PLAYER_DECEL) {
				player->vel.x = 0.0f;
			}
		}
	}
	
	if (inputKeyHeld('A') && player->vel.x > -PLAYER_MAX_SPEED) {
		player->vel.x -= PLAYER_ACCEL * core->time.dt;
	} else {
		if (player->vel.x < 0.0f) {
			player->vel.x += PLAYER_DECEL * core->time.dt;
			if (player->vel.x >= -PLAYER_DECEL) {
				player->vel.x = 0.0f;
			}
		}
	}
}