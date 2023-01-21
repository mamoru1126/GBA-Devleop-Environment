// BG�Ɋւ���ݒ�

#ifndef	BG_H
#define BG_H
#ifdef __cplusplus
extern "C" {
#endif

// REG_DISPCNT

// BG���[�h
#define DISP_BGMODE(x)	(x)
// ���[�h�S�C�T�ŕ\������o�b�t�@
#define DISP_SELECTBUFFER(x)	((x)<<4)

// Hblank���̃X�v���C�g�`��v���Z�X����
#define DISP_HBLANK_PROCESS_ON	(0<<5)
#define DISP_HBLANK_PROCESS_OFF	(1<<5)

// �X�v���C�g�̃}�b�s���O���@
#define DISP_SPRITE_TYPE_1D	(1<<6)
#define DISP_SPRITE_TYPE_2D	(0<<6)

// BG�`��̋����u�����N
#define DISP_FORCE_BLANK	(1<<7)

// BG��X�v���C�g�ʁA�E�B���h�E�̕\���ݒ�
#define DISP_BG0	(1<<8)
#define DISP_BG1	(1<<9)
#define DISP_BG2	(1<<10)
#define DISP_BG3	(1<<11)
#define DISP_OBJ	(1<<12)

#define DISP_WND0	(1<<13)
#define DISP_WND1	(1<<14)
#define DISP_OBJWND	(1<<15)


// REG_DISPSTAT

// Vblank,Hblank,Vcount�̌��݂̏��
#define DSTAT_BIT_VBLANK	(1)
#define DSTAT_BIT_HBLANK	(1<<1)
#define DSTAT_BIT_VCOUNT	(1<<2)

#define DSTAT_USE_VBLANK	(1<<3)
#define DSTAT_USE_HBLANK	(1<<4)
#define DSTAT_USE_VCOUNT	(1<<5)

#define DSTAT_VCOUNT_LINE(x)	((x)<<8)



// BGxCNT�ɓ����ݒ�

// BG�̑傫��
// BG0,1�̏ꍇ
#define	BG_SIZEA_256_256	0
#define	BG_SIZEA_512_256	(1<<14)
#define	BG_SIZEA_256_512	(2<<14)
#define	BG_SIZEA_512_512	(3<<14)
// BG2,3�̏ꍇ
#define	BG_SIZEB_128_128	0
#define	BG_SIZEB_256_256	(1<<14)
#define	BG_SIZEB_512_512	(2<<14)
#define	BG_SIZEB_1024_1024	(2<<14)

// BG2,3�̂݉�]���ɃI�[�o�[���b�v����ꍇ
#define	BG_OVERLAP	(1<<13)

// �X�N���[���x�[�X�A�h���X ���l�~2KB  0-31
#define BG_MAPBASE(x)	((x)<<8)

// BG�J���[���[�h
#define	BG_COLOR_16		0
#define	BG_COLOR_256	(1<<7)

// ���U�C�N�ݒ�
#define	BG_MOZAIC_ON	(1<<6)

// BG�L�����N�^�x�[�X�A�h���X ���l�~16KB  0-3
#define	BG_CHARBASE(x)	((x)<<2)

// �D�揇�� 0-3 0�ɋ߂��قǑO�ʂɕ`��
#define	BG_PRIORITY(x)	(x)



// �}�b�v�f�[�^�ݒ�

// 16�F�p���b�g�̏ꍇ ���l�̃p���b�g�ԍ����g��
#define	BG_MAP_PAL(x)	((x)<<12)

// X,Y�����̃t���b�v
#define	BG_MAP_YFLIP	(1<<11)
#define	BG_MAP_XFLIP	(1<<10)

// �g�p����^�C���ԍ����w�肷��
#define	BG_MAP_TILE(x)	(x)


// VRAM�Ń^�C���L�����N�^���w�肷��ʒu
// BG_CHARBASE(x)�Ɠ������l������
#define	MEM_BG_CHR(x)	((u16*)(0x6000000 + (x)*0x4000))

// VRAM�Ń}�b�v�f�[�^���w�肷��ʒu
// BG_MAPBASE(x)�Ɠ������l������
#define	MEM_BG_MAP(x)	((u16*)(0x6000000 + (x)* 0x800))

// BG�������A�h���X
#define	MEM_BG_PAL	((u16*)0x5000000)

#ifdef __cplusplus
}
#endif
#endif
