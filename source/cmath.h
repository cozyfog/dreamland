/* date = August 12th 2023 5:03 pm */

#ifndef CMATH_H
#define CMATH_H

#include <math.h>
#include "typedef.h"
#include "vector.h"

internal f32 *newOrthoProjectionMatrix(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar) {
	f32 *m = (f32*)malloc(sizeof(float) * 16);
	
	f32 rml = right - left;
	f32 tmb = top - bottom;
	f32 fmn = zfar - znear;
	
	m[0] = 2 / rml;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;
	
	m[4] = 0.0f;
	m[5] = 2 / tmb;
	m[6] = 0.0f;
	m[7] = 0.0f;
	
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = -2.0 / fmn;
	m[11] = 0.0f;
	
	m[12] = -((right + left) / rml);
	m[13] = -((top + bottom) / tmb);
	m[14] = -((zfar  + znear) / fmn);
	m[15] = 1.0f;
	
	return m;
}

#endif //CMATH_H
