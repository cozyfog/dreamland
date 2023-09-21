/* date = September 1st 2023 6:04 pm */

#ifndef INPUT_H
#define INPUT_H

#include "typedef.h"

void inputKeyPressCallback(u8 keycode);
void inputKeyReleaseCallback(u8 keycode);
bool inputKeyHeld(u8 keycode);

#endif //INPUT_H
