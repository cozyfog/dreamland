/* date = August 10th 2023 7:31 pm */

// Created by: Daniel Nickel

#ifndef LIBFF_H
#define LIBFF_H

#include <stdio.h>
#include <stdlib.h>
#if defined(_UTILS_WIN32)
#include <windows.h>
#endif

typedef struct {
	short width;
	short height;
	unsigned char *data;
} LIBFF_Texture;

static LIBFF_Texture LIBFF_textureLoad(const char *filename) {
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
#if defined(_UTILS_WIN32)
		MessageBoxA(NULL, "LIBFF_Error: texture file does not exist or could not be opened.\n", "_utils_win32", MB_OK | MB_ICONERROR);
#else
		printf("LIBFF_Error: file '%s' does not exist or could not be opened.\n", filename);
#endif
	}
	
	LIBFF_Texture texture;
	
	texture.width = fgetc(file) + 1;
	texture.height = fgetc(file) + 1;
	
	int texture_scale = texture.width * texture.height * 3;
	texture.data = (unsigned char*)malloc(sizeof(unsigned char) * texture_scale);
	
	fread(texture.data, texture_scale, 1, file);
	fclose(file);
	
	return texture;
}

#endif //LIBFF_H
