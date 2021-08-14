#ifndef GENBLOBS_H
#define GENBLOBS_H

#include "main.h"

enum {
	GEN_ROTO,
	GEN_ROTO80,
	GEN_PLASMA,
	GEN_DRAWTEXT
};

void generate(int genNum, ScreenResolution *screenRes, bool is486);

#endif
