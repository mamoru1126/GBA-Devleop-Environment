
#include "inc.h"

#include "bios_arm.h"
#include "gbfs.h"
#include "lib.h"
#include "main.h"

#include "screen.h"

//---------------------------------------------------------------------------
//lib.c
extern ST_FONT Font;


ST_SCREEN_IMG  ScreenImg  EWRAM_DATA;
u32 dummy ALIGN(4);
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgInit()
{
	LibMode3SetScreenBuffer((u16*)&ScreenImg.buf);
	dummy = 0;

	WaitForVsync();
	ScreenImgClear();
	ScreenImgUpdate();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgLoad(u16* pData)
{
	Mode3DrawImage(0, 0, SCREEN_CX, SCREEN_CY, pData);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgClear()
{
	CpuSet((u32)&dummy, (u32)ScreenImg.buf, ((SCREEN_CX * SCREEN_CY * 2) / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgUpdate()
{
	CpuSet((u32)ScreenImg.buf, (u32)VideoBuffer, ((SCREEN_CX * SCREEN_CY * 2) / 4) | CPUSET_32BIT);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgFadeIn(u16 mode, u16 min, u16 max, u16 wait)
{
	Mode3DrawBlend(mode, min, max);
	Mode3DrawFadeIn(wait);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgFadeOut(u16 wait)
{
	Mode3DrawFadeOut(wait);
}




//---------------------------------------------------------------------------
EWRAM_CODE void ScreenSprInit()
{

}
//---------------------------------------------------------------------------
EWRAM_CODE void ScreenSprUpdate()
{

}
