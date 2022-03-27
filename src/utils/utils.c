#include "utils.h"

float lerp(float x0, float x1, float alpha) {
    return (1 - alpha) * x0 + alpha * x1;
}

void toPolar(const Vector3Df *point, float *theta, float *phi, float *r) {
    *r = vector3df_length(point);
    *theta = atan2f(point->x, point->y);
    *phi = acosf(point->z / *r);
}