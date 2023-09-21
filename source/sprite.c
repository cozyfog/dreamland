#define _UTILS_WIN32

#include "stb_image.h"
#include "gl/glew.h"
#include "typedef.h"
#include "utils.h"

global i32 width;
global i32 height;
global i32 channels;

void spriteLoad(u32 *id, const char *filename) {
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
	
	assert(data, str_add("Error: sprite loading failed. filename: ", filename));
	
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}