/* date = August 12th 2023 5:35 pm */

#ifndef VECTOR_H
#define VECTOR_H

#include "typedef.h"
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

vec2 vec2_add_vec2(vec2 a, vec2 b);
vec2 vec2_sub_vec2(vec2 a, vec2 b);

vec3 vec3_add_vec3(vec3 a, vec3 b);
vec3 vec3_sub_vec3(vec3 a, vec3 b);

vec2 vec2_mul(vec2 vec, f32 n);
vec3 vec3_mul(vec3 vec, f32 n);

vec2 vec2_div(vec2 vec, f32 n);
vec3 vec3_div(vec3 vec, f32 n);

f32 vec3_distance(vec3 a, vec3 b);

#endif //VECTOR_H
