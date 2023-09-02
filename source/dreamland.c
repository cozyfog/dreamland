#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "input.h"
#include<windows.h>

#define PLAYER_SPEED   4.0f

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
		player->vel.y -= 0.02f * core->time.dt;
	}
	
	// NOTE(daniel): Keep both so I don't have to add checks for stuff like wen 'A' && 'D'.
	//               It theoratically cancels itself out.
	
	player->vel.x = (inputKeyHeld('D') - inputKeyHeld('A')) * PLAYER_SPEED * 0.1f;
	
	if (inputKeyPress(' ')) {
		OutputDebugString("true\n");
		player->vel.y = 5;
		return;
	}
	OutputDebugString("false\n");
}