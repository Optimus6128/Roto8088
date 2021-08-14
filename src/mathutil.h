#ifndef MATHUTIL_H
#define MATHUTIL_H

#define PI 3.14159265359f

#include "types.h"

void initSinTab16(const int numSines, const int repeats, const int amplitude, int *mySinTab);
void initSinTab8(const int numSines, const int repeats, const int amplitude, uint8 *mySinTab);

#endif
