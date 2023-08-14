/* date = August 2nd 2023 4:45 pm */

#ifndef UTILS_H
#define UTILS_H

#ifdef _UTILS_WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

#include <stdlib.h>
#include <stdbool.h>

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

#endif //UTILS_H
