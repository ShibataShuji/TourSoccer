/*==============================================================================

   ���_�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SIZE_X	(100.0f)
#define PLAYER_SIZE_Y	(100.0f)
#define PLAYER_SIZE_Z	(0.0f)			// ���݂����ȃy���y���Ȃ̂ł�����0��OK,�t�ɐ�������Ɨ����̂ɂȂ�̂ŕ\������O�ɂ��Ă��܂��B(player��p�̕\�����@�ɂ����OK)

#define PLAYER_COL_SIZE_X	(100.0f)
#define PLAYER_COL_SIZE_Y	(100.0f)
#define PLAYER_COL_SIZE_Z	(5.0f)		// �\���I�ɂ͈Ⴄ���Ǔ����蔻��͍���Ă����B


// �v���C���[�\����
struct PLAYER
{

	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		oldpos;		// �O�̈ʒu
	D3DXVECTOR3		nextpos;	// ���̈ʒu
	D3DXVECTOR3		drawpos;	// ���ۂ̕\���̈ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		size;		// �傫��
	D3DXVECTOR3		colsize;	// �����蔻��̑傫��
	D3DXVECTOR3		scl;		// �傫���̔{��

	int				texNo;		// �e�N�X�`��
	int				act;		// �ǂ�������Ԃ�(�A�j���[�V�����Ƃ��̎��g��)

	D3DXVECTOR3		move;		// �ړ��̗�,�L�[����͂��Ă��Ȃ���Ζ��t���[�����ƂɎ~�܂낤�Ƃ���,�󒆂Ƃ�����₷���Ŏ~�܂낤�Ƃ���͕͂ς��

	bool			ground;		// �n�ʂɑ���t���Ă����Ԃ��ǂ���


	bool			isUse;		// true:�g���Ă���  false:���g�p

	int				OldBlock_RightEnd;	// 1�t���[���O�̉E�[�̃u���b�N�̒l
	int				OldBlock_UpEnd;		// 1�t���[���O�̏�[�̃u���b�N�̒l
	int				OldBlock_BehindEnd;	// 1�t���[���O�̉��[�̃u���b�N�̒l
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
