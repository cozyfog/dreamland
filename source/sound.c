#define _UTILS_WIN32
#include "utils.h"
#include "typedef.h"
#include "sound.h"
#include "miniaudio.h"

ma_result result;
ma_engine engine;

void soundEntry() {
	result = ma_engine_init(NULL, &engine);
	assert(result == MA_SUCCESS, str_add("Error: Initializing audio engine failed. error_code:", int_to_str(result)));
}

Sound *soundLoad(const char *filename) {
	ma_sound *sound = (ma_sound*)malloc(sizeof(ma_sound));
	ma_result result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, sound);
	assert(result == MA_SUCCESS, str_add("Loading sound failed! filename: ", filename));
	return (Sound*)sound;
}

void soundPlay(Sound *sound) {
	ma_sound_start((ma_sound*)sound);
}

bool soundPlaying(Sound *sound) {
	return !ma_sound_at_end((const ma_sound*)sound);
}

void soundStop(Sound *sound) {
	ma_sound_stop((ma_sound*)sound);
}

f32 soundGetVolume(Sound *sound) {
	return ma_sound_get_volume(sound);
}

void soundSetVolume(Sound *sound, f32 volume) {
	ma_sound_set_volume(sound, volume);
}