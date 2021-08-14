#include <i86.h>
#include <math.h>
#include <stdlib.h>

#include "types.h"

#include "fx_roto.h"
#include "d_roto.h"

#include "mathutil.h"
#include "dio.h"
#include "video.h"

static bool isFxRotoInit = false;

#define ROT_SINTAB_AMPLITUDE 256
#define ROT_SINTAB_SIZE 256
static int rotSinTab[ROT_SINTAB_SIZE];

typedef struct color
{
	uint8 r,g,b;
}color;

static color textCols[16] = {{0,0,0}, {0,0,170}, {0,170,0}, {0,170,170}, {170,0,0}, {170,0,170}, {170,85,170}, {170,170,170}, {85,85,85}, {85,85,255}, {85,255,85}, {85,255,255}, {255,85,85}, {255,85,255}, {255,255,85}, {255,255,255}};

static uint8 mapVGAtoCGA(color *c)
{
	uint8 i = 0;
	uint8 nearI = 0;
	uint16 nearC = 65535;
	const uint8 focusR = 16;
	const uint8 focusG = 4;
	const uint8 focusB = 8;
	do {
		const uint16 dist = abs(textCols[i].r - c->r)*focusR + abs(textCols[i].g - c->g)*focusG + abs(textCols[i].b - c->b)*focusB;
		if (dist < nearC) {
			nearC = dist;
			nearI = i;
		}
	}while(++i < 16);
	return nearI;
}

static void initTextureDracul()
{
	uint8 far *texDest = (uint8 far *)MK_FP(0x8000,0);

	color col;
	uint8 *src = (uint8*)draculin_pal;
	uint8 vgacolmap[256];
	uint8 i = 0;
	do {
		col.r = *src++ << 2;
		col.g = *src++ << 2;
		col.b = *src++ << 2;
		vgacolmap[i] = mapVGAtoCGA(&col);
	}while(++i);

	int count = 0;
	do{
		//int bg = (count >> 2) & 7;
		*(texDest + count) = 0;//(bg << 4) | bg;
	}while(++count);

	src = (uint8*)draculin_spr;
	const int xOff = 160;
	const int yOff = 128;
	const int xl = *src++;
	const int yl = *src++;
	for (int y = 0; y<yl; ++y) {
		for (int x = 0; x<xl; ++x) {
			const uint8 c = vgacolmap[*src++];
			*(texDest + ((y + yOff)<<8) + x + xOff) = (c << 4) | c;
		}
	}
}

void fxRotoInit()
{
	initTextureDracul();
	initSinTab16(ROT_SINTAB_SIZE, 1, ROT_SINTAB_AMPLITUDE, rotSinTab);

	setPseudoScreen160xY(VRAM_LINES_50);

	isFxRotoInit = true;
}

static void fxRotoRunAsm80x50(int idx, int idy, uint16 vramStart)
{
	_asm
	{
		push bp
		push ds

		mov ax,08000h
		mov ds,ax
		mov es,[vramStart]

		mov si,[idx]
		mov bp,[idy]

		xor cx,cx
		mov ax,40
		mul si
		sub cx,ax
		xor dx,dx

		xor di,di

		mov ah,50
		roty:
			push ax
			push cx
			push dx

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

				inc di
				mov bl,ch
				mov bh,dh
				mov al,[bx]
				add cx,si
				add dx,bp
				stosb

			pop dx
			pop cx
			add cx,bp
			sub dx,si

			pop ax
			dec ah
		jz fthis
		jmp roty
	fthis:

	pop ds
	pop bp
	}
}

void fxRotoRun(int fxFrame, uint16 vramStart)
{
	if (!isFxRotoInit) fxRotoInit();

	const int t = fxFrame << 1;
	const int angle = t & 255;
	const int zoom = (rotSinTab[(t >> 1) & (ROT_SINTAB_SIZE-1)] >> 3) + 64;

	const int idx = (rotSinTab[(angle + 64) & 255] * zoom) >> 4;
	const int idy = (rotSinTab[angle] * zoom) >> 4;

	fxRotoRunAsm80x50(idx, idy, vramStart);
}
