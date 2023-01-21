
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include "gbaimg.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode3DrawImage(u16* img)
{
	u16* ScreenBuffer = (u16*)0x6000000;
	u32  x, y;

	for(y=0; y<160; y++)
	{
		for(x=0; x<240; x++)
		{
			ScreenBuffer[y*240+x] = img[y*240+x];
		}
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	// モード設定
	SetMode(MODE_3 | BG2_ENABLE);

	// 画像の読み込み
	Mode3DrawImage((u16*)&gbaimgBitmap);

	for(;;)
	{
	    WaitForVsync();
	}
}


