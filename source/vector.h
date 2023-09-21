/* date = August 12th 2023 5:35 pm */

#ifndef VECTOR_H
#define VECTOR_H

#include "typedef.h"
#include "cute_c2.h"

typedef struct {
	f32 x;
	f32 y;
} vec2;

typedef struct {
	f32 x;
	f32 y;
	f32 z;
} vec3;

internal vec2 vec2_add_vec2(vec2 a, vec2 b) { return (vec2){a.x + b.x, a.y + b.y}; }
internal vec2 vec2_sub_vec2(vec2 a, vec2 b) { return (vec2){a.x - b.x, a.y - b.y}; }

internal vec3 vec3_add_vec3(vec3 a, vec3 b) { return (vec3){a.x + b.x, a.y + b.y, a.z+ b.z}; }
internal vec3 vec3_sub_vec3(vec3 a, vec3 b) { return (vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

internal c2v vec3_to_c2v(vec3 v) {
	return (c2v){v.x, v.y};
}

#endif //VECTOR_H
