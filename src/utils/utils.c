#include "utils.h"

float lerp(float x0, float x1, float alpha) {
    return (1 - alpha) * x0 + alpha * x1;
}

void toPolar(Vector3f *point, float *theta, float *phi, float *r) {
    *r = lengthVector3f(point);
    *theta = atan2f(point->x, point->y);
    *phi = acosf(point->z / *r);
}