#include "inc.h"
#include "gbfs.h"
#include "lib.h"
#include "minix.h"
#include "haribote.h"

#include "invader.h"

//---------------------------------------------------------------------------
ST_INVADER Invader;


//---------------------------------------------------------------------------
EWRAM_CODE void InvaderInit()
{
	_Memset((u8*)&Invader, 0x00, sizeof(ST_INVADER));
}
//---------------------------------------------------------------------------
EWRAM_CODE void InvaderReset()
{
	ST_INVADER* p = &Invader;

	p->pMyShip   = MyShipAlloc();
	p->pMyBullet = NULL;

	u16 cnt = 0;
	u16 sprNo;
	u16 ex, ey;
	u16 x,  y;

	for(y=0; y<ENEMY_MAX_Y; y++)
	{
		for(x=0; x<ENEMY_MAX_X; x++)
		{
			sprNo = 10 + cnt;
			ex    = ENEMY_SX + (ENEMY_CX + ENEMY_NX) * x;
			ey    = ENEMY_SY + (ENEMY_CY + ENEMY_NY) * y;

			p->pEnemy[cnt] = EnemyAlloc(sprNo, ex, ey);
			cnt++;
		}
	}

	p->enemyCnt   = cnt;
	p->enemyMoveX = 4;
	p->enemyMoveY = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InvaderDraw()
{
	ST_INVADER* p = &Invader;

	MyShipDraw(p->pMyShip);

	if(p->pMyBullet != NULL)
	{
		MyBulletDraw(p->pMyBullet);
	}

	u16 i;
	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] != NULL)
		{
			EnemyDraw(p->pEnemy[i]);
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void InvaderAct()
{
	ST_INVADER* p = &Invader;

	MyShipAct(p->pMyShip);

	if( MyShipIsShot(p->pMyShip) == TRUE )
	{
		if(p->pMyBullet == NULL)
		{
			p->pMyBullet = MyBulletAlloc(p->pMyShip);
		}
	}

	if(p->pMyBullet != NULL)
	{
		MyBulletAct(p->pMyBullet);
	}

	if(p->enemyActTime < ENEMY_MAX_ACT_TIME)
	{
		p->enemyActTime++;
		return;
	}
	p->enemyActTime = 0;


	switch(p->enemyActNo)
	{
	case 0:		//âE
		if( InvaderGetAllEnemyMaxX() > SCREEN_CX - 16 )
		{
			p->enemyActNo  = 1;
			p->enemyActCnt = 4;
			p->enemyMoveX  = 0;
			p->enemyMoveY  = 4;
		}
		break;

	case 1:		//â∫
		p->enemyActCnt--;

		if(p->enemyActCnt == 0)
		{
			p->enemyActNo  =  2;
			p->enemyMoveX  = -6;
			p->enemyMoveY  =  0;
		}
		break;

	case 2:		//ç∂
		if( InvaderGetAllEnemyMinX() < 16 )
		{
			p->enemyActNo  = 3;
			p->enemyActCnt = 4;
			p->enemyMoveX  = 0;
			p->enemyMoveY  = 4;
		}
		break;

	case 3:		//â∫
		p->enemyActCnt--;

		if(p->enemyActCnt == 0)
		{
			p->enemyActNo  = 0;
			p->enemyMoveX  = 6;
			p->enemyMoveY  = 0;
		}
	}

	InvaderAllEnemyAct();
}
//---------------------------------------------------------------------------
EWRAM_CODE s16 InvaderGetAllEnemyMaxX()
{
	ST_INVADER* p = &Invader;
	s16 max = 0;
	u16 i;

	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] == NULL)
		{
			continue;
		}

		if(max < p->pEnemy[i]->x + p->pEnemy[i]->cx)
		{
			max = p->pEnemy[i]->x + p->pEnemy[i]->cx;
		}
	}

	return max;
}
//---------------------------------------------------------------------------
EWRAM_CODE s16 InvaderGetAllEnemyMaxY()
{
	ST_INVADER* p = &Invader;
	s16 max = 0;
	u16 i;

	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] == NULL)
		{
			continue;
		}

		if(max < p->pEnemy[i]->y + p->pEnemy[i]->cy)
		{
			max = p->pEnemy[i]->y + p->pEnemy[i]->cy;
		}
	}

	return max;
}
//---------------------------------------------------------------------------
EWRAM_CODE s16 InvaderGetAllEnemyMinX()
{
	ST_INVADER* p = &Invader;
	s16 min = SCREEN_CX;
	u16 i;

	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] == NULL)
		{
			continue;
		}

		if(min > p->pEnemy[i]->x)
		{
			min = p->pEnemy[i]->x;
		}
	}

	return min;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InvaderAllEnemyAct()
{
	ST_INVADER* p = &Invader;
	u16 i;

	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] == NULL)
		{
			continue;
		}

		EnemyAct(p->pEnemy[i], p->enemyMoveX, p->enemyMoveY);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool InvaderIsGameOver()
{
	ST_INVADER* p = &Invader;
	bool ret = FALSE;
	
	ret |= (InvaderGetAllEnemyMaxY() > (SCREEN_CY - MYSHIP_CY)) ? TRUE : FALSE;
	ret |= (p->enemyCnt == 0) ? TRUE : FALSE;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE void InvaderHit()
{
	ST_INVADER* p = &Invader;
	ST_TASK*    b = p->pMyBullet;
	ST_TASK*    e = NULL;

	if(b == NULL)
	{
		return;
	}

	if((b->y + b->cy) < 0)
	{
		goto BDestroy;
	}

	u16 i;
	for(i=0; i<ENEMY_MAX_CNT; i++)
	{
		if(p->pEnemy[i] == NULL)
		{
			continue;
		}

		e = p->pEnemy[i];

		if( InvaderIsHitBox(b->x, b->y, b->cx, b->cy, e->x, e->y, e->cx, e->cy) == TRUE )
		{
			goto HDestroy;
		}
	}

	return;

HDestroy:
	SpriteMove(e->sprNo, SCREEN_CX, SCREEN_CY);
	MyMemFree((u32)e, sizeof(ST_TASK));
	p->pEnemy[i] = NULL;
	p->enemyCnt--;

BDestroy:
	SpriteMove(b->sprNo, SCREEN_CX, SCREEN_CY);
	MyMemFree((u32)b, sizeof(ST_TASK));
	p->pMyBullet = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool InvaderIsHitBox(u16 sx, u16 sy, u16 scx, u16 scy, u16 dx, u16 dy, u16 dcx, u16 dcy)
{
	if( (sy < dy + dcy) && (dy < sy + scy) )
	{
		if( (sx < dx + dcx) && (dx < sx + scx) )
		{
			return TRUE;
		}
	}

	return FALSE;
}




//---------------------------------------------------------------------------
EWRAM_CODE ST_TASK* MyShipAlloc()
{
	ST_TASK* p = (ST_TASK*)MyMemAlloc(sizeof(ST_TASK));

	p->x      = (SCREEN_CX - MYSHIP_CX) / 2;
	p->y      = (SCREEN_CY - MYSHIP_CY) - 2;
	p->cx     = MYSHIP_CX;
	p->cy     = MYSHIP_CY;
	p->sprNo  = 0;
	p->tileNo = MYSHIP_TILENO;
	p->var1   = 0;
	p->var2   = 0;

	SpriteSetSize(p->sprNo, SP_SIZE_32, SP_SQUARE, SP_COLOR_16);
	SpriteSetChr (p->sprNo, p->tileNo);

	return p;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MyShipDraw(ST_TASK* p)
{
	SpriteMove(p->sprNo, p->x, p->y);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MyShipAct(ST_TASK* p)
{
	u16 key = KeyGet2();

	if(key & KEY_A)
	{
		p->var1 = 1;
	}
	else
	{
		p->var1 = 0;
	}

	if(key & KEY_LEFT)
	{
		if(p->x > 0)
		{
			p->x-= 2;
		}
	}

	if(key & KEY_RIGHT)
	{
		if((p->x + p->cx) < SCREEN_CX)
		{
			p->x+= 2;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool MyShipIsShot(ST_TASK* p)
{
	return (p->var1 == 1) ? TRUE : FALSE;
}




//---------------------------------------------------------------------------
EWRAM_CODE ST_TASK* MyBulletAlloc(ST_TASK* pMyShip)
{
	ST_TASK* p = (ST_TASK*)MyMemAlloc(sizeof(ST_TASK));

	p->x      = pMyShip->x + (pMyShip->cx / 2) - (MYBULLET_CX / 2);
	p->y      = pMyShip->y;
	p->cx     = MYBULLET_CX;
	p->cy     = MYBULLET_CY;
	p->sprNo  = 1;
	p->tileNo = MYBULLET_TILENO;
	p->var1   = 0;
	p->var2   = 0;

	SpriteSetSize(p->sprNo, SP_SIZE_16, SP_SQUARE, SP_COLOR_16);
	SpriteSetChr (p->sprNo, p->tileNo);

	return p;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MyBulletDraw(ST_TASK* p)
{
	SpriteMove(p->sprNo, p->x, p->y);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MyBulletAct(ST_TASK* p)
{
	p->y -= 4;
}




//---------------------------------------------------------------------------
EWRAM_CODE ST_TASK* EnemyAlloc(u16 sprNo, s16 x, s16 y)
{
	ST_TASK* p = (ST_TASK*)MyMemAlloc(sizeof(ST_TASK));

	p->x      = x;
	p->y      = y;
	p->cx     = ENEMY_CX;
	p->cy     = ENEMY_CY;
	p->sprNo  = sprNo;
	p->tileNo = ENEMY_TILENO;
	p->var1   = 0;
	p->var2   = 0;

	SpriteSetSize(p->sprNo, SP_SIZE_32, SP_SQUARE, SP_COLOR_16);
	SpriteSetChr (p->sprNo, p->tileNo);

	return p;
}
//---------------------------------------------------------------------------
EWRAM_CODE void EnemyDraw(ST_TASK* p)
{
	SpriteMove(p->sprNo, p->x, p->y);
}
//---------------------------------------------------------------------------
EWRAM_CODE void EnemyAct(ST_TASK* p, s16 x, s16 y)
{
	p->x += x;
	p->y += y;
}
