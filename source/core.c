#include <windows.h>
#include "core.h"
#include "typedef.h"
#include "vector.h"

global Core core;

Core *getGlobalCore() {
	return &core;
}

void coreUpdateTime() {
	f32 ct = GetTickCount() * 0.0001f;
	if (core.time.lt == 0.0f)
		core.time.lt = ct;
	core.time.dt = (ct - core.time.lt) * 60.0f;
	core.time.lt = ct;
}