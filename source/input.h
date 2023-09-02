/* date = September 1st 2023 6:04 pm */

#ifndef INPUT_H
#define INPUT_H

#include "typedef.h"

void inputCallback(u8 keycode, bool held);
bool inputKeyHeld(u8 keycode);
bool inputKeyPress(u8 keycode);
bool inputKeyRelease(u8 keycode);

#endif //INPUT_H
