//�u30���łł���I�n�r�������v�̃\�[�X�R�[�h���g�킹�Ē����Ă��܂��B
//���C�Z���X�́u�썇�����C�Z���X-01�v�ł��Bhttp://hrb.osask.jp/
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

	//free[]��addr���ɕ��ׂ�ׁAfree[]�̑}���ꏊ�����߂܂�
	for(i=0; i<p->cnt; i++)
	{
		if(p->freeInfo[i].addr > addr)
		{
			break;
		}
	}

	//�O�̋󂫗̈悪���邩�`�F�b�N�����܂�
	if( (i > 0) && (p->freeInfo[i-1].addr + p->freeInfo[i-1].size == addr) )
	{
		p->freeInfo[i-1].size += size;

		//���̋󂫗̈悪���邩�`�F�b�N�����܂�
		if( (i < p->cnt) && (addr + size == p->freeInfo[i].addr) )
		{
			p->freeInfo[i-1].size += p->freeInfo[i].size;
			p->cnt--;

			//free[i]���Ȃ��Ȃ����̂őO�֋l�߂܂�
			while(i < p->cnt)
			{
				p->freeInfo[i] = p->freeInfo[i + 1];
				i++;
			}
		}

		return TRUE;
	}

	//�O�̋󂫗̈�Ƃ܂Ƃ߂��Ȃ������ꍇ�A��낪���邩�`�F�b�N�����܂�
	if( (i < p->cnt) && (addr + size == p->freeInfo[i].addr) )
	{
		p->freeInfo[i].addr  = addr;
		p->freeInfo[i].size += size;

		return TRUE;
	}


	//�O�ɂ����̗̈�ɂ��܂Ƃ߂��Ȃ��ꍇ�Afree[i]����ɂ��炵�Č��Ԃ����܂�
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

				//free[i]���Ȃ��Ȃ����̂őO�֋l�߂܂�
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
