/* date = August 2nd 2023 4:45 pm */

#ifndef UTILS_H
#define UTILS_H

#ifdef _UTILS_WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void assert(bool cond, const char *msg) {
	if (!cond) {
#ifdef _UTILS_WIN32
		MessageBoxA(NULL, msg, "_utils_win32", MB_OK | MB_ICONERROR);
#else
		printf("%s\n", msg);
#endif
		exit(1);
	}
}

static char *str_add(const char *a, const char *b) {
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);
	
	char *result = (char*)malloc(sizeof(char) * (a_len + b_len));
	
	for (size_t i = 0; i < a_len; ++i) {
		result[i] = a[i];
	}
	
	for (size_t i = 0; i < b_len; ++i) {
		result[a_len + i] = b[i];
	}
	
	return result;
}

static char *int_to_str(int n) {
	char *result = (char*)malloc(sizeof(char) * 10);
	sprintf(result, "%d", n);
	return result;
}

#endif //UTILS_H
