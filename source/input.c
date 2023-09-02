#include "typedef.h"
#include "input.h"

bool last_kb[256] = {0};
bool keyboard[256] = {0};

void inputCallback(u8 keycode, bool held) {
	last_kb[keycode] = keyboard[keycode];
	keyboard[keycode] = held;
}

bool inputKeyHeld(u8 keycode) {
	return keyboard[keycode];
}

bool inputKeyPress(u8 keycode) {
	return (!last_kb[keycode] && keyboard[keycode]);
}

bool inputKeyRelease(u8 keycode) {
	return (last_kb[keycode] && !keyboard[keycode]);
}

