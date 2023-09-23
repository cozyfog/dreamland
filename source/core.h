/* date = August 4th 2023 10:24 pm */

#ifndef CORE_H
#define CORE_H

#include "typedef.h"
#include "vector.h"
#include "entity.h"

class(Core) {
	struct {
		f32 dt;
		f32 lt;
		u64 tick;
	} time;
	
	Entity *entities[MAX_ENTITY_COUNT];
	u64 entity_count;
};

Core *getGlobalCore();
void coreUpdateTime();

#endif //CORE_H
