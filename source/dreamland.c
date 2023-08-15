#include "typedef.h"
#include "dreamland.h"
#include "core.h"
#include "entity.h"
#include "win32_input.h"

#define PLAYER_SPEED   8

global Core *core;
global Entity *player;
global Win32InputProfile last_profile;

internal void controllerCallback(Win32InputProfile profile) {
	if (profile.stick_x > 0) {
		player->pos.x += PLAYER_SPEED * core->time.dt;
	} else if (profile.stick_x < 0) {
		player->pos.x -= PLAYER_SPEED * core->time.dt;
	}
	
	if (profile.button_a) OutputDebugString("true\n");
	else OutputDebugString("false\n");
	
	last_profile = profile;
}

void dreamlandEntry() {
	win32SetControllerCallback(controllerCallback);
	
	core = getGlobalCore();
	player = newEntity((vec3){0.0f, 15.0f, 0.0f}, (vec3){28.0f, 28.0f, 1.0f}, "sprites/player_idle_test.tff");
}

void dreamlandUpdate() {
	if (player->pos.y <= 0.0f) {
		player->pos.y = 0.0f;
	} else {
		player->vel.y -= 0.2f * core->time.dt;
	}
}
