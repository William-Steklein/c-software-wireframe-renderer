#ifndef C_TEST_UTILS_H
#define C_TEST_UTILS_H

#include "../DataStructures/Vector3f.h"

float lerp(float x0, float x1, float alpha);

void toPolar(Vector3f *point, float *theta, float *phi, float *r);

#endif //C_TEST_UTILS_H
