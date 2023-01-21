
#ifndef __MAIN_H__
#define __MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
//ÉvÉçÉOÉâÉÄÇÃèÛë‘
enum {
	STATE_INIT  = 0x01,
	STATE_RESET,
	STATE_DRAW,
	STATE_ACT,
	STATE_HIT,
	STATE_END,
};


//---------------------------------------------------------------------------
EWRAM_CODE void StateInit(); 
EWRAM_CODE void StateReset();
EWRAM_CODE void StateDraw();
EWRAM_CODE void StateAct();
EWRAM_CODE void StateHit();
EWRAM_CODE void StateEnd();

EWRAM_CODE void InitWS();
EWRAM_CODE void InitLib();
EWRAM_CODE void InitKey();
EWRAM_CODE void InitIRQ();
EWRAM_CODE void InitFont();
EWRAM_CODE void InitSprite();


EWRAM_CODE void SystemError(char* msg1, char* msg2);


#ifdef __cplusplus
}
#endif
#endif
