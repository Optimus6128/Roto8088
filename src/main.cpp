#include <stdio.h>
#include <conio.h>
#include <i86.h>

#include "main.h"
#include "types.h"
#include "video.h"
#include "timer.h"
#include "mathutil.h"
#include "drawtext.h"

#include "fx_roto.h"
#include "fx_plasm.h"


static bool vsync = true;

static int nframe = 0;
static bool quit = false;

static int npart = PART_ROTO;

static void input()
{
	if (kbhit())
	{
		uint8 key = getch();
		switch(key)
		{
			case 27:    // Escape
				quit = true;
			break;

			case 32:    // Space
				npart = (npart + 1) % NUM_PARTS;
			break;

			case 'f':
				vsync = !vsync;
			break;
		}
	}
}

static char *text = "                          hello    this is optimus bringing you a single effect demo with a scrolltext and no music          \
no time to do something more polished and with more effects or find out how to play music           \
first time i code something exclusively for the xt pc           i simply reported some effects from vga to pseudo videomode in cga text     \
it gets fifteen fps in my xt pc but i know i can do better in the future       i still wanted to release something for pcjam no matter how lame so here it is      \
scroller will restart now                             \0";

int prevTime = -1;

static void scroll(int time)
{
	uint8 far *dst = (uint8 far *)MK_FP(0xB800+0xA*45,0);

	char *textOff = text + (time >> 2);

	uint8 pOff = 6 - (((time & 3) >> 0) << 1);
	for (int i=0; i<20; ++i) {
		char c = textOff[i];
		if (c>=97 && c<=122) {
			c = c - 97;
			drawFont(c, dst + pOff);
		}
		pOff += 8;
	}

	if (textOff[20]=='\0') {
		prevTime = -1;
	}
}

static void script(int fxFrame, int part)
{
	switch (part)
	{
		case PART_ROTO:
			fxRotoRun(fxFrame);
		break;

		case PART_PLASMA:
			fxPlasmaRun(fxFrame);
		break;

		default:
		break;
	}

	if (prevTime == -1) prevTime = getTime();

	int time = getTime() - prevTime;
	scroll(time);
}

static void preInitParts()
{
	fxRotoInit();
}

int main()
{
	detectGfxCard();

	setMode(0x03);

	int time0 = getTime();
	while(!quit)
	{
		if (vsync) waitForVsync();
		script(nframe, npart);
		input();
		++nframe;
	}
	int time1 = getTime();

	setMode(0x03);

	float secs = (float)(time1 - time0) / TIME_FREQ;
	float fps = (float)nframe / secs;
	printf("%.2f Fps\n", fps);
	
	return 0;
}
