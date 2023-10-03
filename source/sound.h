/* date = September 23rd 2023 2:10 pm */

#ifndef SOUND_H
#define SOUND_H

#include "typedef.h"
#include "miniaudio.h"

typedef ma_sound Sound;

void soundEntry();
Sound *soundLoad(const char *filename);
void soundPlay(Sound *sound);
bool soundPlaying(Sound *sound);
void soundStop(Sound *sound);
f32 soundGetVolume(Sound *sound);
void soundSetVolume(Sound *sound, f32 volume);

#endif //SOUND_H
