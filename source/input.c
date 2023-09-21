#include "typedef.h"
#include "input.h"

bool last_kb[256] = {0};
bool keyboard[256] = {0};

void inputKeyPressCallback(u8 keycode) {
	last_kb[keycode] = keyboard[keycode];
	keyboard[keycode] = true;
	if (last_kb[keycode]) return;
}

void inputKeyReleaseCallback(u8 keycode) {
	last_kb[keycode] = keyboard[keycode];
	keyboard[keycode] = false;
	if (!last_kb[keycode]) return;
}

bool inputKeyHeld(u8 keycode) {
	return keyboard[keycode];
}