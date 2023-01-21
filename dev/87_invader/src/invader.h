
#ifndef __INVADER_H__
#define __INVADER_H__
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
#define MYSHIP_CX				32
#define MYSHIP_CY				16
#define MYSHIP_TILENO			516

#define MYBULLET_CX				2
#define MYBULLET_CY				16
#define MYBULLET_TILENO			576

#define ENEMY_SX				40
#define ENEMY_SY				8
#define ENEMY_CX				32
#define ENEMY_CY				16
#define ENEMY_NX				8								//“G‚Æ“G‚Æ‚ÌŠÔ
#define ENEMY_NY				4
#define ENEMY_MAX_X				4
#define ENEMY_MAX_Y				4
#define ENEMY_MAX_CNT			(ENEMY_MAX_X * ENEMY_MAX_Y)
#define ENEMY_TILENO			520
#define ENEMY_MAX_ACT_TIME		10

//---------------------------------------------------------------------------

typedef struct {
	s16  x;
	s16  y;
	s16  cx;
	s16  cy;
	u16  sprNo;
	u16  tileNo;
	s16  var1;
	s16  var2;
} ST_TASK ALIGN(4);

typedef struct {
	ST_TASK* pMyShip;
	ST_TASK* pMyBullet;
	ST_TASK* pEnemy[ENEMY_MAX_CNT];

	u16 enemyActTime;
	u8  enemyActNo;
	u8  enemyActCnt;
	s16 enemyMoveX;
	s16 enemyMoveY;
	u16 enemyCnt;
} ST_INVADER;

//---------------------------------------------------------------------------
EWRAM_CODE void InvaderInit();
EWRAM_CODE void InvaderReset();
EWRAM_CODE void InvaderDraw();
EWRAM_CODE void InvaderAct();
EWRAM_CODE void InvaderHit();

EWRAM_CODE void InvaderAllEnemyAct();
EWRAM_CODE s16  InvaderGetAllEnemyMaxX();
EWRAM_CODE s16  InvaderGetAllEnemyMaxY();
EWRAM_CODE s16  InvaderGetAllEnemyMinX();

EWRAM_CODE bool InvaderIsGameOver();
EWRAM_CODE bool InvaderIsHitBox(u16 sx, u16 sy, u16 scx, u16 scy, u16 dx, u16 dy, u16 dcx, u16 dcy);


//----
EWRAM_CODE ST_TASK* MyShipAlloc();
EWRAM_CODE void MyShipDraw(ST_TASK* p);
EWRAM_CODE void MyShipAct(ST_TASK* p);
EWRAM_CODE bool MyShipIsShot(ST_TASK* p);


//----
EWRAM_CODE ST_TASK* MyBulletAlloc(ST_TASK* p);
EWRAM_CODE void MyBulletDraw(ST_TASK* p);
EWRAM_CODE void MyBulletAct(ST_TASK* p);


//----
EWRAM_CODE ST_TASK* EnemyAlloc(u16 sprNo, s16 x, s16 y);
EWRAM_CODE void EnemyDraw(ST_TASK* p);
EWRAM_CODE void EnemyAct(ST_TASK* p, s16 x, s16 y);



#ifdef __cplusplus
}
#endif
#endif

