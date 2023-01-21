
#ifndef __HARIBOTE_H__
#define __HARIBOTE_H__
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
#define MYMEM_MAX_FREE_INFO			20
#define MYMEM_SIZE					2000

//---------------------------------------------------------------------------
typedef struct {
	u32 addr;
	u32 size;
} ST_MYMEM_FREE_INFO;

typedef struct {
	u32 cnt;												//ãÛÇ´èÓïÒÇÃå¬êî
	ST_MYMEM_FREE_INFO freeInfo[MYMEM_MAX_FREE_INFO];
} ST_MYMEM;


//---------------------------------------------------------------------------
EWRAM_CODE void MyMemInit();

EWRAM_CODE u32  MyMemGetFreeSize();

EWRAM_CODE bool MyMemFree(u32 addr, u32 size);
EWRAM_CODE u8*  MyMemAlloc(u32 size);



#ifdef __cplusplus
}
#endif
#endif

