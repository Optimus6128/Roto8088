#ifndef VIDEO_H
#define VIDEO_H

enum VramLines
{
	VRAM_LINES_50,
	VRAM_LINES_100
};

extern bool isVGA;

void setMode(int mode);
void waitForVsync();
void detectGfxCard();
void pageFlipPseudo160x50(int page);
void setPseudoScreen160xY(VramLines lines);

#endif
