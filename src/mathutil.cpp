#include "mathutil.h"

#include <math.h>

void initSinTab8(const int numSines, const int repeats, const int amplitude, uint8 *mySinTab)
{
	const int numSinesRepeat = numSines / repeats;
	float sMul = (2.0f * PI) / (float)(numSinesRepeat-1);
	for (int i=0; i<numSines; ++i) {
		mySinTab[i] = (uint8)(sin((float)i * sMul) * amplitude);
	}
}

void initSinTab16(const int numSines, const int repeats, const int amplitude, int *mySinTab)
{
	const int numSinesRepeat = numSines / repeats;
	float sMul = (2.0f * PI) / (float)(numSinesRepeat-1);
	for (int i=0; i<numSines; ++i) {
		mySinTab[i] = (int)(sin((float)i * sMul) * amplitude);
	}
}
