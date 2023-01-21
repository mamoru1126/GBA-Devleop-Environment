
#include "inc.h"

#include "minix.h"
#include "irq_arm.h"
#include "bios_arm.h"
#include "div_arm.h"
#include "ad_arm.h"
#include "gbfs.h"
#include "lib.h"
#include "rand.h"

#include "screen.h"
#include "invader.h"
#include "haribote.h"
#include "main.h"


//#include "header\font\BGFont.h"


//Mode3
//BG2 メッセージ
//Spr 自機、敵機、自弾

//---------------------------------------------------------------------------
u8 State;

//---------------------------------------------------------------------------
EWRAM_CODE int main()
{
	State = STATE_INIT;

	for(;;)
	{
		switch(State)
		{
			case STATE_INIT:  StateInit();  break;
			case STATE_RESET: StateReset(); break;
			case STATE_DRAW:  StateDraw();  break;
			case STATE_ACT:   StateAct();   break;
			case STATE_HIT:   StateHit();   break;
			case STATE_END:   StateEnd();   break;

			default:
				DebugMessage("[Err] main State");
				break;
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateInit()
{
	InitWS();
	InitLib();
	InitKey();
	InitIRQ();
	InitFont();
	InitSprite();

	SetMode(MODE_3 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_2D);

	State = STATE_RESET;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitWS()
{
	REG_WSCNT = 0x4317;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitLib()
{
	LibInit();
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitKey()
{
	KeyInit();
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitIRQ()
{
	REG_INTERUPT = (u32)IRQUserHandler;
	REG_IE       = IRQ_BIT_TIMER2;

	REG_TM2D     = 65536 - 2621;			// (((16*1024*1024) / 64) * 10) / 1000
	REG_TM2CNT   = TM_ENABLE | TM_FREQ_PER_64 | TM_USEIRQ;

	REG_IME      = IRQ_MASTER_ON;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitFont()
{
	ST_FONT_SRC half;		//半角文字

	half.pDat   = (u8*)&mplus_s10rBitmap;
	half.pSheet = (u16*)&mplus_sfnt_txt;
	half.imgCx  = MPLUS_S10R_IMG_CX;
	half.cnt    = MPLUS_S10R_FONT_CNT;
	half.cx     = MPLUS_S10R_FONT_CX;
	half.cy     = MPLUS_S10R_FONT_CY;

	Mode3SetFont(NULL, &half);
}
//---------------------------------------------------------------------------
EWRAM_CODE void InitSprite()
{
	SpriteInit();

	SpriteSetPalData16((u16*)&sprPal);
	SpriteSetData((u16*)&sprTiles, sprTilesLen);
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateReset()
{
	ScreenImgInit();
	InvaderInit();
	MyMemInit();

	InvaderReset();

	State = STATE_DRAW;
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateDraw()
{
	WaitForVsync();
	InvaderDraw();

	State = STATE_ACT;
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateAct()
{
	InvaderAct();

	State = STATE_HIT;
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateHit()
{
	InvaderHit();

	State = (InvaderIsGameOver() == TRUE) ? STATE_END : STATE_DRAW;
}
//---------------------------------------------------------------------------
EWRAM_CODE void StateEnd()
{
	u16 cy = 11;

	Mode3DrawFontStr(0,  0, (u8*)"GAME OVER"    , COLOR_WHITE);
	Mode3DrawFontStr(0, cy, (u8*)"PUSH B BUTTON", COLOR_WHITE);
	WaitForVsync();
	ScreenImgUpdate();

	KeyWait(KEY_B);

	State = STATE_RESET;
}



//---------------------------------------------------------------------------
EWRAM_CODE void SystemError(char* msg1, char* msg2)
{
	u16 cy = 11;

	ScreenImgFadeOut(0);
	LibMode3SetScreenBuffer((u16*)VideoBuffer);

	if(msg1 != NULL) Mode3DrawFontStr(0,  0, (u8*)msg1, COLOR_WHITE);
	if(msg2 != NULL) Mode3DrawFontStr(0, cy, (u8*)msg2, COLOR_WHITE);

	for(;;){}
}
