/* date = August 12th 2023 5:35 pm */

#ifndef VECTOR_H
#define VECTOR_H

#include "typedef.h"
#include "cute_c2.h"
#include "math.h"

class(vec2) {
	f32 x;
	f32 y;
};

class(vec3) {
	f32 x;
	f32 y;
	f32 z;
};

internal vec2 vec2_add_vec2(vec2 a, vec2 b) { return (vec2){a.x + b.x, a.y + b.y}; }
internal vec2 vec2_sub_vec2(vec2 a, vec2 b) { return (vec2){a.x - b.x, a.y - b.y}; }

internal vec3 vec3_add_vec3(vec3 a, vec3 b) { return (vec3){a.x + b.x, a.y + b.y, a.z+ b.z}; }
internal vec3 vec3_sub_vec3(vec3 a, vec3 b) { return (vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

internal vec2 vec2_mul(vec2 vec, f32 n) { return (vec2){vec.x * n, vec.y * n}; }
internal vec3 vec3_mul(vec3 vec, f32 n) { return (vec3){vec.x * n, vec.y * n, vec.z * n}; }

internal c2v vec2_to_c2v(vec2 v) { return (c2v){v.x, v.y}; }
internal c2v vec3_to_c2v(vec3 v) { return (c2v){v.x, v.y}; }

internal f32 square(f32 n) { return n * n; }
internal f32 vec3_distance(vec3 a, vec3 b) {
	return sqrt(square(b.x - a.x) + square(b.y - a.y) + square(b.z - a.z));
}

#endif //VECTOR_H
