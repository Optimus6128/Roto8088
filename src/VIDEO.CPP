#include <i86.h>
#include <string.h>
#include <stdlib.h>
#include "video.h"
#include "dio.h"
#include "types.h"

bool isVGA = false;

void setMode(int mode)
{
	_asm
	{
		mov ax,mode
		int 10h
	}
}

void detectGfxCard()
{
	_asm
	{
		mov ax,1a00h
		int 10h
		cmp al,1ah
		jnz notSupported
		mov [isVGA],1
		jmp endDetect
notSupported:
		mov [isVGA],0
endDetect:
	}
}

void waitForVsync()
{
	_asm
	{
		mov dx,3dah

		vsync_in:
			in al,dx
			and al,8
		jnz vsync_in

		vsync_out:
			in al,dx
			and al,8
		jz vsync_out
	}
}

static void disableTextBlink()
{
	_asm
	{
		mov al,[isVGA]
		or al,al
		jnz disableBlinkVGA

		mov ax,40h
		mov es,ax
		mov dx,[es:63h]		;get port address of the card
		add dx,4

		mov al,[es:65h]		;get current value of Mode Select Register
		and al,0dfh			;mask value by 1101 1111 (to clear bit 5)
		out dx,al			;disable blink
		mov [es:065h],al	;save the new setting
		
		jmp disableBlinkEnd

disableBlinkVGA:
		mov ax,1003h		;do it for VGA too
		mov bl,0
		int 10h
disableBlinkEnd:
	}
}

static void preparePseudoScreen()
{
	uint16 far *vram = (uint16 far *)MK_FP(0xB800,0);
	for (int i=0; i<16000; ++i) {
		*vram++ = 0x00DE;
	}

	disableTextBlink();
}

static void setPseudo160x100_CGA()
{
	outb(0x3D4, 0x04);
	outb(0x3D5, 0x7F);

	outb(0x3D4, 0x06);
	outb(0x3D5, 0x64);

	outb(0x3D4, 0x07);
	outb(0x3D5, 0x70);

	outb(0x3D4, 0x09);
	outb(0x3D5, 0x01);
}

static void setPseudo160x50_CGA()
{
	outb(0x3D4, 0x04);
	outb(0x3D5, 0x3F);

	outb(0x3D4, 0x06);
	outb(0x3D5, 0x32);

	outb(0x3D4, 0x07);
	outb(0x3D5, 0x38);

	outb(0x3D4, 0x09);
	outb(0x3D5, 0x03);
}

static void setPseudo160x100_VGA()
{
	outb(0x3D4, 0x09);
	outb(0x3D5, 0x03);
}

static void setPseudo160x50_VGA()
{
	outb(0x3D4, 0x09);
	outb(0x3D5, 0x07);
}

void setPseudoScreen160xY(VramLines lines)
{
	setMode(0x03);

	switch(lines){
		case VRAM_LINES_50:
			if (isVGA) {
				setPseudo160x50_VGA();
			} else {
				setPseudo160x50_CGA();
			}
		break;

		case VRAM_LINES_100:
			if (isVGA) {
				setPseudo160x100_VGA();
			} else {
				setPseudo160x100_CGA();
			}
		break;
	}

	preparePseudoScreen();
}
