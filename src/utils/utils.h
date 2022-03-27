#ifndef SIMPLE_C_GRAPHICS_ENGINE_UTILS_H
#define SIMPLE_C_GRAPHICS_ENGINE_UTILS_H

#include "../DataStructures/Vector3Df.h"

float lerp(float x0, float x1, float alpha);

void toPolar(const Vector3Df *point, float *theta, float *phi, float *r);

#endif //SIMPLE_C_GRAPHICS_ENGINE_UTILS_H
