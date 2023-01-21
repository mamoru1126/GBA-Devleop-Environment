//「30日でできる！ＯＳ自作入門」のソースコードを使わせて頂いています。
//ライセンスは「川合堂ライセンス-01」です。http://hrb.osask.jp/
#include "inc.h"
#include "minix.h"
#include "main.h"

#include "haribote.h"

//---------------------------------------------------------------------------
ST_MYMEM MyMem;
u8       MyMemRam[MYMEM_SIZE];

//---------------------------------------------------------------------------
EWRAM_CODE void MyMemInit()
{
	_Memset((u8*)&MyMem,    0x00, sizeof(ST_MYMEM)  );
	_Memset((u8*)&MyMemRam, 0x00, sizeof(MYMEM_SIZE));

	MyMemFree((u32)&MyMemRam, MYMEM_SIZE);
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 MyMemGetFreeSize()
{
	ST_MYMEM* p = &MyMem;

	u32 freeSize = 0;
	u16 i;

	for(i=0; i<p->cnt; i++)
	{
		freeSize += p->freeInfo[i].size;
	}

	return freeSize;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool MyMemFree(u32 addr, u32 size)
{
	ST_MYMEM* p = &MyMem;
	u16 i, j;

//	TRACEOUT("%x %x\n", addr, size);

	//free[]をaddr順に並べる為、free[]の挿入場所を決めます
	for(i=0; i<p->cnt; i++)
	{
		if(p->freeInfo[i].addr > addr)
		{
			break;
		}
	}

	//前の空き領域があるかチェックをします
	if( (i > 0) && (p->freeInfo[i-1].addr + p->freeInfo[i-1].size == addr) )
	{
		p->freeInfo[i-1].size += size;

		//後ろの空き領域があるかチェックをします
		if( (i < p->cnt) && (addr + size == p->freeInfo[i].addr) )
		{
			p->freeInfo[i-1].size += p->freeInfo[i].size;
			p->cnt--;

			//free[i]がなくなったので前へ詰めます
			while(i < p->cnt)
			{
				p->freeInfo[i] = p->freeInfo[i + 1];
				i++;
			}
		}

		return TRUE;
	}

	//前の空き領域とまとめられなかった場合、後ろがあるかチェックをします
	if( (i < p->cnt) && (addr + size == p->freeInfo[i].addr) )
	{
		p->freeInfo[i].addr  = addr;
		p->freeInfo[i].size += size;

		return TRUE;
	}


	//前にも後ろの領域にもまとめられない場合、free[i]より後にずらして隙間を作ります
	if(p->cnt < MYMEM_MAX_FREE_INFO)
	{
		for(j=p->cnt; j>i; j--)
		{
			p->freeInfo[j] = p->freeInfo[j-1];
		}
		p->cnt++;

		p->freeInfo[i].addr = addr;
		p->freeInfo[i].size = size;

		return TRUE;
	}

	SystemError("MemFree Error", NULL);
	return FALSE;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* MyMemAlloc(u32 size)
{
	ST_MYMEM* p = &MyMem;
	u8* addr;
	u16 i;

	for(i=0; i<p->cnt; i++)
	{
		if(p->freeInfo[i].size >= size)
		{
			addr = (u8*)p->freeInfo[i].addr;

			p->freeInfo[i].addr += size;
			p->freeInfo[i].size -= size;

			if(p->freeInfo[i].size == 0)
			{
				p->cnt--;

				//free[i]がなくなったので前へ詰めます
				while(i < p->cnt)
				{
					p->freeInfo[i] = p->freeInfo[i + 1];
					i++;
				}
			}

			//TRACEOUT("MyMemAlloc addr=0x%x size=%d \n", addr, size);
			return addr;
		}
	}

	SystemError("MemAlloc Error", NULL);
	return NULL;
}
