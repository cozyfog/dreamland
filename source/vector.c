#include "typedef.h"
#include "vector.h"


vec2 vec2_add_vec2(vec2 a, vec2 b) { return (vec2){a.x + b.x, a.y + b.y}; }
vec2 vec2_sub_vec2(vec2 a, vec2 b) { return (vec2){a.x - b.x, a.y - b.y}; }

vec3 vec3_add_vec3(vec3 a, vec3 b) { return (vec3){a.x + b.x, a.y + b.y, a.z+ b.z}; }
vec3 vec3_sub_vec3(vec3 a, vec3 b) { return (vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

vec2 vec2_mul(vec2 vec, f32 n) { return (vec2){vec.x * n, vec.y * n}; }
vec3 vec3_mul(vec3 vec, f32 n) { return (vec3){vec.x * n, vec.y * n, vec.z * n}; }

vec2 vec2_div(vec2 vec, f32 n) { return (vec2){vec.x / n, vec.y / n}; }
vec3 vec3_div(vec3 vec, f32 n) { return (vec3){vec.x / n, vec.y / n, vec.z / n}; }

internal f32 square(f32 n) { return n * n; }
f32 vec3_distance(vec3 a, vec3 b) {
	return sqrt(square(b.x - a.x) + square(b.y - a.y) + square(b.z - a.z));
}
