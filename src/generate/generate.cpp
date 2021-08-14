#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typedefs.h"
#include "generate.h"

#define NUM_LETTERS 26
#define FONT_W 4
#define FONT_H 5

static int letters[NUM_LETTERS][FONT_W*FONT_H] = {
	{
		0,1,0,0,
		1,0,1,0,
		1,1,1,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		1,1,0,0,
		1,0,1,0,
		1,1,0,0,
		1,0,1,0,
		1,1,0,0
	},
	{
		0,1,1,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		0,1,1,0
	},
	{
		1,1,0,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		1,1,0,0
	},
	{
		1,1,1,0,
		1,0,0,0,
		1,1,0,0,
		1,0,0,0,
		1,1,1,0
	},
	{
		1,1,1,0,
		1,0,0,0,
		1,1,0,0,
		1,0,0,0,
		1,0,0,0
	},
	{
		0,1,1,0,
		1,0,0,0,
		1,0,0,0,
		1,0,1,0,
		0,1,1,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		1,1,1,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		1,0,1,0,
		0,1,0,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		1,1,0,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,1,1,0
	},
	{
		1,0,1,0,
		1,1,1,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		1,0,0,0,
		1,1,0,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		0,1,0,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		0,1,0,0
	},
	{
		1,1,0,0,
		1,0,1,0,
		1,1,0,0,
		1,0,0,0,
		1,0,0,0
	},
	{
		0,1,0,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		0,1,1,0
	},
	{
		1,1,0,0,
		1,0,1,0,
		1,1,0,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		0,1,1,0,
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		1,1,0,0
	},
	{
		1,1,1,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		0,1,0,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		1,0,1,0,
		1,1,1,0,
		1,0,1,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		0,1,0,0,
		1,0,1,0,
		1,0,1,0
	},
	{
		1,0,1,0,
		1,0,1,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	{
		1,1,1,0,
		0,0,1,0,
		0,1,0,0,
		1,0,0,0,
		1,1,1,0
	}
};

static void outputDrawText(FILE *f)
{
	fprintf(f, "void drawFont(uint8 c, uint8 far *dst)\n{\n");
	fprintf(f, "\tswitch(c) {\n");

	for (int i=0; i<NUM_LETTERS; ++i) {
		int *ltr = (int*)&letters[i];
		
		fprintf(f, "\t\tcase %d:\n", i);

		for (int x=0; x<FONT_W; ++x) {
			for (int y=0; y<FONT_H; ++y) {
				int c = ltr[y*FONT_W+x];
				const int offset = y*160+2*x+1;
				if (c==1) fprintf(f, "\t\t\t*(dst+%d) = 255;\n", offset);
			}
		}
		fprintf(f, "\t\tbreak;\n\n");
	}
	fprintf(f, "\t\tdefault:\n\t\tbreak;\n\t}\n}\n");
}

static void outputRotoCode(FILE *f, ScreenResolution *screenRes, bool is486)
{
	for (int x=0; x<screenRes->width; x+=4) {
		fprintf(f, "\t\t\t\tmov ah,bh\n");
		fprintf(f, "\t\t\t\txor ah,dh\n");
		fprintf(f, "\t\t\t\tadd bx,si\n");
		fprintf(f, "\t\t\t\tadd dx,cx\n");
		fprintf(f, "\t\t\t\tmov al,bh\n");
		fprintf(f, "\t\t\t\txor al,dh\n");
		fprintf(f, "\t\t\t\tadd bx,si\n");
		fprintf(f, "\t\t\t\tadd dx,cx\n");
		fprintf(f, "\t\t\t\tshl eax,16\n");

		fprintf(f, "\t\t\t\tmov ah,bh\n");
		fprintf(f, "\t\t\t\txor ah,dh\n");
		fprintf(f, "\t\t\t\tadd bx,si\n");
		fprintf(f, "\t\t\t\tadd dx,cx\n");
		fprintf(f, "\t\t\t\tmov al,bh\n");
		fprintf(f, "\t\t\t\txor al,dh\n");
		fprintf(f, "\t\t\t\tadd bx,si\n");
		fprintf(f, "\t\t\t\tadd dx,cx\n");

		if (is486)
			fprintf(f, "\t\t\t\tmov [edi+%d],eax\n\n",316-x);
		else
			fprintf(f, "\t\t\t\tstosd\n\n");
	}
	if (is486) fprintf(f, "\t\t\t\tadd edi,320\n");
}

static void outputRotoCode160x100(FILE *f, ScreenResolution *screenRes)
{
	for (int x=0; x<screenRes->width; x++) {
		fprintf(f, "\t\t\t\tmov bl,ch\n");
		fprintf(f, "\t\t\t\tmov bh,dh\n");
		fprintf(f, "\t\t\t\tmov al,[bx]\n");
		fprintf(f, "\t\t\t\tadd cx,si\n");
		fprintf(f, "\t\t\t\tadd dx,bp\n");
		fprintf(f, "\t\t\t\tstosb\n");
		fprintf(f, "\t\t\t\tinc di\n\n");
	}
}

static void outputRotoCode80x50(FILE *f, ScreenResolution *screenRes)
{
	for (int x=0; x<screenRes->width; x++) {
		fprintf(f, "\t\t\t\tinc di\n");
		fprintf(f, "\t\t\t\tmov bl,ch\n");
		fprintf(f, "\t\t\t\tmov bh,dh\n");
		fprintf(f, "\t\t\t\tmov al,[bx]\n");
		fprintf(f, "\t\t\t\tadd cx,si\n");
		fprintf(f, "\t\t\t\tadd dx,bp\n");
		fprintf(f, "\t\t\t\tstosb\n\n");
	}
}

/*static void outputRotoCode80x50(FILE *f, ScreenResolution *screenRes)
{
	for (int x=0; x<screenRes->width; x++) {
		fprintf(f, "\t\t\t\tmov bl,ch\n");
		fprintf(f, "\t\t\t\tmov bh,dh\n");
		fprintf(f, "\t\t\t\tmov ah,[bx]\n");
		fprintf(f, "\t\t\t\tadd cx,si\n");
		fprintf(f, "\t\t\t\tadd dx,bp\n");
		fprintf(f, "\t\t\t\tstosw\n\n");
	}
}*/

/*static void outputRotoCode80x50(FILE *f, ScreenResolution *screenRes)
{
	for (int x=0; x<screenRes->width; x++) {
		fprintf(f, "\t\t\t\tmov bl,ch\n");
		fprintf(f, "\t\t\t\tmov bh,dh\n");
		fprintf(f, "\t\t\t\tmov al,[bx]\n");
		fprintf(f, "\t\t\t\tadd cx,si\n");
		fprintf(f, "\t\t\t\tadd dx,bp\n");
		fprintf(f, "\t\t\t\tmov [es:di+%d],al\n\n", 1+2*x);
	}
}*/


#define NUM_SINES 2048
uint8 *fsin1;
uint32 fsin1_32[NUM_SINES/4];

static void outputPlasmaCode(FILE *f, ScreenResolution *screenRes, bool is486)
{
	fsin1 = (uint8*)malloc(NUM_SINES * sizeof(*fsin1));
	for (uint32 i=0; i<NUM_SINES; ++i) {
		fsin1[i] = (uint8)(sin(i / 56.0f) * 256.0f + 256.0f);
	}
	for (uint32 i=0; i<NUM_SINES-4; i+=4) {
		fsin1_32[i>>2] = (fsin1[i+3] << 24) | (fsin1[i+2] << 16) | (fsin1[i+1] << 8) | fsin1[i];
	}
	free(fsin1);

	for (int x=0; x<screenRes->width; x+=4) {
		const uint32 fsin1a = fsin1_32[x>>2];
		const uint32 fsin1b = fsin1_32[(x+4)>>2];

		if (x==0) {
			fprintf(f, "\t\t\t\tadd eax,%d\n", fsin1_32[x]);
		} else {
			fprintf(f, "\t\t\t\tadd eax,%d\n", fsin1b-fsin1a);
		}

		if (is486)
			fprintf(f, "\t\t\t\tmov [edi+%d],eax\n",x);
		else
			fprintf(f, "\t\t\t\tstosd\n\n");
	}
	if (is486) fprintf(f, "\t\t\t\tadd edi,320\n");
}

void generate(int genNum, ScreenResolution *screenRes, bool is486)
{
	FILE *f;
	switch(genNum) {
		case GEN_ROTO:
			f = fopen("rotocode.cpp", "w");
			outputRotoCode(f, screenRes, is486);
		break;
		
		case GEN_PLASMA:
			f = fopen("plascode.cpp", "w");
			outputPlasmaCode(f, screenRes, is486);
		break;

		case GEN_ROTO80:
			f = fopen("roto80.cpp", "w");
			outputRotoCode80x50(f, screenRes);
		break;
		
		case GEN_DRAWTEXT:
			f = fopen("drawtext.cpp", "w");
			outputDrawText(f);
		break;

		default:
			return;
	}
	fclose(f);
}
