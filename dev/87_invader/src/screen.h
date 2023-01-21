
#ifndef __SCREEN_H__
#define __SCREEN_H__
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	u16 buf[SCREEN_CX][SCREEN_CY] ALIGN(4);
} ST_SCREEN_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ScreenImgInit();
EWRAM_CODE void ScreenImgLoad(u16* pData);
EWRAM_CODE void ScreenImgClear();
EWRAM_CODE void ScreenImgUpdate();

EWRAM_CODE void ScreenImgFadeIn(u16 mode, u16 min, u16 max, u16 wait);
EWRAM_CODE void ScreenImgFadeOut(u16 wait);


//----
EWRAM_CODE void ScreenSprInit();
EWRAM_CODE void ScreenSprUpdate();


#ifdef __cplusplus
}
#endif
#endif
