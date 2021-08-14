#include <i86.h>
#include <math.h>
#include <string.h>

#include "fx_roto.h"
#include "d_roto.h"

#include "mathutil.h"
#include "video.h"

static bool isFxPlasmaInit = false;

#define PLASMA_SINTAB_SIZE 768
uint8 isin1[PLASMA_SINTAB_SIZE], isin2[PLASMA_SINTAB_SIZE];

void fxPlasmaInit()
{
	initSinTab8(PLASMA_SINTAB_SIZE, 12, 64, isin1);
	initSinTab8(PLASMA_SINTAB_SIZE, 8, 92, isin2);
}

void fxPlasmaRun(int fxFrame)
{
	if (!isFxPlasmaInit) {
		fxPlasmaInit();
		isFxPlasmaInit = true;
	}

	uint16 far *vram = (uint16 far *)MK_FP(0xA000,0);
	for (int y=0; y<96; ++y) {
		uint16 *psin2 = (uint16*)isin2;
		const uint8 yp8 = isin1[(y+fxFrame) & 255] + (y<<1);
		const uint16 yp = (uint16)((yp8 << 8) | yp8);
		for (int x=0; x<40; x+=8) {
			*vram++ = yp + *(psin2);
			*vram++ = yp + *(psin2+1);
			*vram++ = yp + *(psin2+2);
			*vram++ = yp + *(psin2+3);
			*vram++ = yp + *(psin2+4);
			*vram++ = yp + *(psin2+5);
			*vram++ = yp + *(psin2+6);
			*vram++ = yp + *(psin2+7);
			psin2+=8;
		}
	}
}
