/*==============================================================================

   ���_�Ǘ� [player.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
//#include "bullet.h"
#include "score.h"
//#include "sound.h"
//#include "bg.h"
#include "polygon.h"
#include "map.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER g_Player;
static int g_ShotSENo = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{

	//
	//g_ShotSENo = LoadSound("data/SE/shot000.wav");

	// �e�N�X�`������
	g_Player.texNo = LoadTexture("data/TEXTURE/player.png");

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Player.size	 = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);							// �z�u�̑傫��
	g_Player.colsize = D3DXVECTOR3(PLAYER_COL_SIZE_X, PLAYER_COL_SIZE_Y, PLAYER_COL_SIZE_Z);							// �����蔻��̑傫��
	g_Player.pos     = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// �z�u������W
	g_Player.oldpos  = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// �O�̃t���[���̍��W��ۑ�
	g_Player.nextpos = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// ���̃t���[���̍��W�̌v�Z�Ŏg�p
	g_Player.drawpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �z�u������W
	g_Player.rot     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �z�u�̊p�x
	g_Player.scl     = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// �傫���̔{��

	g_Player.move    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��̗�

	g_Player.act = 0;

	g_Player.ground = true;

	g_Player.isUse = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{

	// oldpos�̐ݒ�
	g_Player.oldpos = g_Player.pos;


	// move�ړ��̗͂̐ݒ�(�A�b�v�f�[�g�̍ŏ��ɏ����Ƃ�������)(0.0f�ɋ߂Â��Ă���)
	float friction;					// ���C��,��R��(���Ƃ��󒆂Ƃ����������̂ɂ���ĕύX����)
	float AirResistance;			// ��C��R
	float max_fall_speed = 8.0f;	// �����ɂ��ő呬�x
	friction = 0.3f;
	AirResistance = 0.15f;
		// x�̐ݒ�
	if (g_Player.move.x > 0)
	{
		g_Player.move.x = g_Player.move.x - friction;
		if (g_Player.move.x < 0)
			g_Player.move.x = 0;
	}
	if (g_Player.move.x < 0)
	{
		g_Player.move.x = g_Player.move.x + friction;
		if (g_Player.move.x > 0)
			g_Player.move.x = 0;
	}
		// y�̐ݒ�
		// �n�ʂɂ����Ԃł����
	if (g_Player.ground == true)
	{
		if (g_Player.move.y > 0)
		{
			g_Player.move.y = g_Player.move.y - friction;
			if (g_Player.move.y < 0)
				g_Player.move.y = 0;
		}
		if (g_Player.move.y < 0)
		{
			g_Player.move.y = g_Player.move.y + friction;
			if (g_Player.move.y > 0)
				g_Player.move.y = 0;
		}
		g_Player.move.y = 0.0f;		// �n�ʂɂ��邩�炱��ł�������
	}
	else
	{
		// �n�ʂɂ��Ȃ���Ԃł����
		g_Player.move.y = g_Player.move.y - AirResistance;
		if (g_Player.move.y < -max_fall_speed)
			g_Player.move.y = -max_fall_speed;
	}
		// z�̐ݒ�
	if (g_Player.move.z > 0)
	{
		g_Player.move.z = g_Player.move.z - friction;
		if (g_Player.move.z < 0)
			g_Player.move.z = 0;
	}
	if (g_Player.move.z < 0)
	{
		g_Player.move.z = g_Player.move.z + friction;
		if (g_Player.move.z > 0)
			g_Player.move.z = 0;
	}


	// �L�[���͂ɂ��ړ��̐ݒ�
	// ���̂Ȃɂ��ɂ���ăL�[���͂ɂ��ő�X�s�[�h�𒴂��Ă��Ă��L�[���͂ɂ��ő�X�s�[�h�Ƀ��Z�b�g����Ȃ��悤�ɂ��Ă�
	float max_speed_for_kye = 4.0f;

	if (GetKeyboardPress(DIK_UP))
	{
			// g_Player.pos.z -= 1.0f;
			
			if (g_Player.move.z < max_speed_for_kye)
			{
				// �L�[���͂ɂ��ő�X�s�[�h�ɂȂ�悤�ɒ���,����𒴂��邱�Ƃ͂Ȃ��悤�ɂ���B���𑫂�
				if (g_Player.move.z > max_speed_for_kye - 1.0f)
				{
					g_Player.move.z += max_speed_for_kye - g_Player.move.z;
				}
				else
					g_Player.move.z += 1.0f;
			}
	}

	if (GetKeyboardPress(DIK_DOWN))
	{
			// g_Player.pos.z += 1.0f;

		if (g_Player.move.z > -max_speed_for_kye)
		{
			// �L�[���͂ɂ��ő�X�s�[�h�ɂȂ�悤�ɒ���,����𒴂��邱�Ƃ͂Ȃ��悤�ɂ���B���𑫂�
			if (g_Player.move.z < -max_speed_for_kye + 1.0f)
			{
				g_Player.move.z += -max_speed_for_kye - g_Player.move.z;
			}
			else
				g_Player.move.z -= 1.0f;
		}

	}

	if (GetKeyboardPress(DIK_LEFT))
	{
			// g_Player.pos.x -= 1.0f;

		if (g_Player.move.x > -max_speed_for_kye)
		{
			// �L�[���͂ɂ��ő�X�s�[�h�ɂȂ�悤�ɒ���,����𒴂��邱�Ƃ͂Ȃ��悤�ɂ���B���𑫂�
			if (g_Player.move.x < -max_speed_for_kye + 1.0f)
			{
				g_Player.move.x += -max_speed_for_kye - g_Player.move.x;
			}
			else
				g_Player.move.x -= 1.0f;
		}

	}

	if (GetKeyboardPress(DIK_RIGHT))
	{
			// g_Player.pos.x += 1.0f;

		if (g_Player.move.x < max_speed_for_kye)
		{
			// �L�[���͂ɂ��ő�X�s�[�h�ɂȂ�悤�ɒ���,����𒴂��邱�Ƃ͂Ȃ��悤�ɂ���B���𑫂�
			if (g_Player.move.x > max_speed_for_kye - 1.0f)
			{
				g_Player.move.x += max_speed_for_kye - g_Player.move.x;
			}
			else
				g_Player.move.x += 1.0f;
		}

	}


	// move�ɂ��ړ���nextpos���W�ɓK�p������
	g_Player.nextpos.x += g_Player.move.x;
	g_Player.nextpos.y += g_Player.move.y;
	g_Player.nextpos.z += g_Player.move.z;

	// surface�̓T�C�R���̂ǂ̖ʂ�`���܂����B0:����,1:��둤,2:�㑤,3:����,4:�E��,5:����

	// nextpos���g���ē����蔻��̌v�Z������,�ŏI�I��pos��nextpos��K�p����
	// �@nextpos����v���C���[�����ǂ�




	////�}�b�v1�֐؂�ւ���
	//if (GetKeyboardTrigger(DIK_L))
	//{
	//	SetCurrentMap(1);
	//}
	////�}�b�v0�֐؂�ւ���
	//if (GetKeyboardTrigger(DIK_K))
	//{
	//	SetCurrentMap(0);
	//}


	//// �e����
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	PlaySound(g_ShotSENo, 0);

	//	SetVolume(g_ShotSENo, 0.1f);

	//	D3DXVECTOR2 pos = g_Player.pos;
	//	SetBullet(pos);		// �P����
	//	AddScore(123);
	//}

	//�����A�j���[�V����
	if (g_AnimeWaitFrame > 10)
	{
		g_AnimePtn++;
		if (g_AnimePtn > 2)
			g_AnimePtn = 0;

		g_AnimeWaitFrame = 0;
	}
	g_AnimeWaitFrame++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	// pos �� drawpos �ɕϊ����鏈��
	// ���͂܂��}�b�v����������ĂȂ����炻�̂܂܁B
	g_Player.drawpos = g_Player.pos;

	SetScore(g_Player.drawpos.x);

	// ���t���[���X�V����̂ōŊ��̏�����J�E���g�� 1 
	SetObject(0, g_Player.texNo, g_Player.drawpos, g_Player.rot, g_Player.size, g_Player.scl,
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
}

//=============================================================================
// �v���C���[�\���̂̐擪�A�h���X���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}


