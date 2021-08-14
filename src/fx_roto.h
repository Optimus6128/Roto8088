#ifndef FX_ROTO_H
#define FX_ROTO_H

#define FP_MUL 65536
#define FP_SHR 16

void fxRotoInit();
void fxRotoRun(int fxFrame, uint16 vramStart);

#endif
