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
#include <math.h>


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
	g_Player.pos     = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// �z�u������W
	g_Player.oldpos  = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// �O�̃t���[���̍��W��ۑ�
	g_Player.nextpos = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// ���̃t���[���̍��W�̌v�Z�Ŏg�p
	g_Player.drawpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �z�u������W
	g_Player.rot     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �z�u�̊p�x
	g_Player.scl     = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// �傫���̔{��

	g_Player.move    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ��̗�

	g_Player.act = 0;

	g_Player.ground = true;

	g_Player.isUse = false;



	g_Player.OldBlock_RightEnd = 0;
	g_Player.OldBlock_UpEnd = 0;
	g_Player.OldBlock_BehindEnd = 0;

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

	// oldpos,oldblock�̐ݒ�
	g_Player.oldpos = g_Player.pos;
	// pos���獡����u���b�N�͂ǂ��������߂�
	int oldblock_x = (g_Player.oldpos.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int oldblock_y = (g_Player.oldpos.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int oldblock_z = (g_Player.oldpos.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	// oldpos�̎��̍��W��8�����v�Z�ŋ��߂�,�����蔻��Ȃ̂�size�ł͂Ȃ�colsize���g��
	D3DXVECTOR3 LUFold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUFold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDFold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDFold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));

	D3DXVECTOR3 LUBold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUBold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDBold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDBold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));

	//���_����old�㉺���E�O���̃u���b�N�����߂�
	int LeftBlockOld   = (LUFold.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int RightBlockOld  = (RUFold.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int UpBlockOld	   = (LUFold.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int DownBlockOld   = (LDFold.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int FrontBlockOld  = (LUFold.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;
	int BehindBlockOld = (LUBold.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	// 0.5f���炵�č��E��㉺�ł̂��ꂪ�łȂ��悤����
	RightBlockOld  = (RUFold.x - 0.5f + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	UpBlockOld     = (LUFold.y - 0.5f + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	BehindBlockOld = (LUBold.z - 0.5f + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	//if (RightBlockOld > oldblock_x && oldblock_x == LeftBlockOld)
	//	RightBlockOld = oldblock_x;
	//if (UpBlockOld > oldblock_y && oldblock_y == DownBlockOld)
	//	UpBlockOld = oldblock_y;
	//if (BehindBlockOld > oldblock_z && oldblock_z == FrontBlockOld)
	//	BehindBlockOld = oldblock_z;


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

	// �������p��nextpos���p�ӂ���
	D3DXVECTOR3 InitNextpos = g_Player.nextpos;

	// �}�b�v�Ƃ̓����蔻��
	// nextpos�̎��̍��W��8�����v�Z�ŋ��߂�,�����蔻��Ȃ̂�size�ł͂Ȃ�colsize���g��
	D3DXVECTOR3 LUF = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUF = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDF = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDF = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));

	D3DXVECTOR3 LUB = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUB = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDB = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDB = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));

	// 8���̍��W���g���A�}�b�v�̂ǂ̃u���b�N����ǂ̃u���b�N�܂ł������ɂ����邩�v�Z����,int�ŏ����_�ȉ��؂�̂Ă����
	int Block_Left  = (LUF.x - (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;			// ���[
	int Block_Right = (RUF.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X + 1;		// �E�[,�����_�ȉ��؂�̂Ă����̂�+1����
	int Block_Up    = (LUF.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y + 1;		// ��[,�����_�ȉ��؂�̂Ă����̂�+1����
	int Block_Down  = (LUB.y - (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;		// ���[,�����_�ȉ��؂�̂Ă����̂�+1����
	int Block_Front = (LUF.z - (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;			// �O�[
	int Block_Back  = (LUB.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z + 1;		// ���[,�����_�ȉ��؂�̂Ă����̂�+1����

	// +1�����Ƃ��Ƀ}�b�v�̍ő�l������Ȃ��悤�ɂ���
	if (Block_Right >= MAP_X_MAX)
		Block_Right = MAP_X_MAX - 1;
	if (Block_Up >= MAP_Y_MAX)
		Block_Up = MAP_Y_MAX - 1;
	if (Block_Back >= MAP_Z_MAX)
		Block_Back = MAP_Z_MAX - 1;


	// move����ǂ̖ʂ������邱�Ƃ��\�z����邩���v�Z����,�����Ă��Ȃ��ƌv�Z�̑ΏۊO�ɂ���
	int ColX = -1;		// move����ʂ̂ǂ��炪�������Ă��邩�𒲂ׂ�,-1:������s��Ȃ�,0:��,1:�E
	int ColY = -1;		// move����ʂ̂ǂ��炪�������Ă��邩�𒲂ׂ�,-1:������s��Ȃ�,0:��,1:��
	int ColZ = -1;		// move����ʂ̂ǂ��炪�������Ă��邩�𒲂ׂ�,-1:������s��Ȃ�,0:�O,1:��
	if (g_Player.move.x > 0.0f)		// �v���C���[�͉E�ɐi��ł���
		ColX = 0;
	if (g_Player.move.x < 0.0f)		// �v���C���[�͍��ɐi��ł���
		ColX = 1;
	if (g_Player.move.y > 0.0f)		// �v���C���[�͏�ɐi��ł���
		ColY = 0;
	if (g_Player.move.y < 0.0f)		// �v���C���[�͉��ɐi��ł���
		ColY = 1;
	if (g_Player.move.z > 0.0f)		// �v���C���[�͉��ɐi��ł���
		ColZ = 0;
	if (g_Player.move.z < 0.0f)		// �v���C���[�͎�O�ɐi��ł���
		ColZ = 1;

	// �������Ă���͈͂̃u���b�N���瓖���蔻��̂���u���b�N���ǂ������}�b�v�`�b�v���璲�ׂ�
	// �������Ă���u���b�N��ۑ����Čォ��v�Z�p
	int hitcount = 0;		// �������Ă���u���b�N�̐�
	D3DXVECTOR3 block_min  = D3DXVECTOR3(999, 999, 999);
	D3DXVECTOR3 block_max  = D3DXVECTOR3(-1, -1, -1);
	D3DXVECTOR3 block_last = D3DXVECTOR3(-1, -1, -1);
	for (int z = Block_Front; z <= Block_Back; z++)
	{
		for (int y = Block_Down; y <= Block_Up; y++)
		{
			for (int x = Block_Left; x <= Block_Right; x++)
			{
				// ���̃u���b�N�������蔻�肪����u���b�N���ǂ������ׂ�
				int BlockData = CheckBlockdata(x, y, z);
				// ���̃u���b�N�f�[�^�� 1 �������瓖���蔻�肪����̂Œ��œ����蔻��̌v�Z���A�������Ă���ʂ�1�ʂɌ��߂�
				if (BlockData == 1)
				{

					if (CheckHitCircleBox(g_Player.nextpos, g_Player.colsize.x,
						D3DXVECTOR3(x, y, z), D3DXVECTOR3(MAPCHIP_COLSIZE_X, MAPCHIP_COLSIZE_Y, MAPCHIP_COLSIZE_Z)))
					{
						// �~�̓����蔻��œ������Ă���ꍇ
						// �������Ă���u���b�N�̕ۑ�
						hitcount++;
						block_last.x = x;
						block_last.y = y;
						block_last.z = z;

						if (x > block_max.x) block_max.x = x;
						if (x < block_min.x) block_min.x = x;
						if (y > block_max.y) block_max.y = y;
						if (y < block_min.y) block_min.y = y;
						if (z > block_max.z) block_max.z = z;
						if (z < block_min.z) block_min.z = z;

					}

					////ChangeBlockdata(2, x, y, z);
					////D3DXVECTOR3
					//// �אڂ��Ă���u���b�N�� 1, �����蔻��̂���u���b�N���ƕ��������̂ŁA�X�ɍׂ��������蔻�������
					//if (CheckHit(g_Player.nextpos, g_Player.colsize,
					//	D3DXVECTOR3(x * MAPCHIP_SIZE_X, y * MAPCHIP_SIZE_Y, z * MAPCHIP_SIZE_Z), D3DXVECTOR3(MAPCHIP_COLSIZE_X, MAPCHIP_COLSIZE_Y, MAPCHIP_COLSIZE_Z)))
					//{
					//	// �������Ă���u���b�N�̕ۑ�
					//	hitcount++;
					//	block_last.x = x;
					//	block_last.y = y;
					//	block_last.z = z;

					//	if (x > block_max.x) block_max.x = x;
					//	if (x < block_min.x) block_min.x = x;
					//	if (y > block_max.y) block_max.y = y;
					//	if (y < block_min.y) block_min.y = y;
					//	if (z > block_max.z) block_max.z = z;
					//	if (z < block_min.z) block_min.z = z;


					//	// �u���b�N��8���̍��W
					//	D3DXVECTOR3 LUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 LDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));

					//	D3DXVECTOR3 LUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 LDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	
					//	//////////// �~���g���������蔻��
					//	//////////// �Ƃ肠����x��z�ł���Ă݂Ă� ���a�̓v���C���[�̓����蔻��̃T�C�Y�̂Ƃ肠����X(50.0f)���g��
					//	//////////float radius = g_Player.colsize.x / 2;
					//	//////////// �܂��~�̌��_�Ƃ����Е��̓_�̋��������߂�
					//	//////////float distance = CalculationDistance(g_Player.nextpos.x, g_Player.nextpos.z, LUF_block.x, LUF_block.z);
					//	//////////// �����Ƃ͕ʂ�x��z�̗����̍����o���Ă��� ���̎��Aobj2 - obj1�ƂȂ�悤�ɂ���B(obj1�̓����Ŕ�����s������)
					//	//////////D3DXVECTOR2 difference = D3DXVECTOR2(g_Player.nextpos.x - LUF_block.x, g_Player.nextpos.z - LUF_block.z);
					//	//////////// ���̋������~�̔��a���Z���Ȃ�~�̒��ɂ��̓_(�l�p�`�̊p)�������Ă���̂œ������Ă���B
						//if (distance <= radius)
						//{
						//	// �������Ă��鏈��
						//	// ���a(�S��)��������ɂł���O�p�`�̎Ε�(=distance)�������Ċ������o��
						//	float ratio = distance / radius;	// �~�̌��_����p�܂ł̋����͔��a�ɑ΂��Ăǂ̂��炢�̊������B
						//	// ���ɑ΂��Ċ����������Ă����āA�~�̌��_�Ɣ���Ă���ŉ��̍��W�̍����o��
						//	D3DXVECTOR2 finpos = D3DXVECTOR2(difference.x / ratio, difference.y / ratio);

						//	// �ŏI�I�ȓ������������o��
						//	D3DXVECTOR2 movedistance = D3DXVECTOR2(finpos.x - difference.x, finpos.y - difference.y);

						//	// �ŏI�I�ɋ��߂����W����p�̍��W�������Ă�����΂ǂꂾ������Ă��邩���킩��
						//	//D3DXVECTOR2 Cover = D3DXVECTOR2(LUF_block.x + finpos.x, LUF_block.z + finpos.y);
						//	// ������nextpos�ɔ��f������B�܂��͍ŏI�I�ɂ�������悤�ɂ���
						//	//g_Player.nextpos.x = g_Player.nextpos.x - movedistance.x;
						//	//g_Player.nextpos.z = g_Player.nextpos.z - movedistance.y;

						//	float assx = g_Player.nextpos.x - movedistance.x;
						//	float assy = g_Player.nextpos.z - movedistance.y;

						//	SetScore(ratio * 100);
						//	//SetScore1(radius + 1000);
						//	//SetScore2(distance + 1000);
						//	SetScore1(movedistance.x + 1000);
						//	SetScore2(movedistance.y + 1000);
						//	SetScore3(finpos.x + 1000);
						//	SetScore4(finpos.y + 1000);
						//	SetScore5(assx + 1000);
						//	SetScore6(assy + 1000);

						//}
					//}
				}

			}
		}

	}

	if (hitcount > 0)
	{
		// �������Ă���ꍇ
		for (int z = block_min.z; z <= block_max.z; z++)
		{
			for (int y = block_min.y; y <= block_max.y; y++)
			{
				for (int x = block_min.x; z <= block_max.x; x++)
				{

					// �u���b�N��8���̍��W
					D3DXVECTOR3 LUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 LDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));

					D3DXVECTOR3 LUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 LDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));

					float radius = g_Player.colsize.x / 2;

					for (int corner = 0; corner < 8; corner++)
					{
						D3DXVECTOR3 Block_pos;
						if (corner == 0)	Block_pos = LUF_block;
						if (corner == 1)	Block_pos = RUF_block;
						if (corner == 2)	Block_pos = LDF_block;
						if (corner == 3)	Block_pos = RDF_block;
						if (corner == 4)	Block_pos = LUB_block;
						if (corner == 5)	Block_pos = RUB_block;
						if (corner == 6)	Block_pos = LDB_block;
						if (corner == 7)	Block_pos = RDB_block;

						float distance = CalculationDistance(g_Player.nextpos.x, g_Player.nextpos.z, Block_pos.x, Block_pos.z);
						D3DXVECTOR2 difference = D3DXVECTOR2(g_Player.nextpos.x - Block_pos.x, g_Player.nextpos.z - Block_pos.z);

						float ratio = distance / radius;
						D3DXVECTOR2 finpos = D3DXVECTOR2(difference.x / ratio, difference.y / ratio);

						// �ŏI�I�ȓ������������o��
						D3DXVECTOR2 movedistance = D3DXVECTOR2(finpos.x - difference.x, finpos.y - difference.y);

						float assx = g_Player.nextpos.x - movedistance.x;
						float assy = g_Player.nextpos.z - movedistance.y;

						SetScore(ratio * 100);
						//SetScore1(radius + 1000);
						//SetScore2(distance + 1000);
						SetScore1(movedistance.x + 1000);
						SetScore2(movedistance.y + 1000);
						SetScore3(finpos.x + 1000);
						SetScore4(finpos.y + 1000);
						SetScore5(assx + 1000);
						SetScore6(assy + 1000);

					}


				}
			}
		}
	}


	// �����蔻�蓙�̌v�Z��nextpos�ōs�������ƍŌ��pos�ɔ��f������
	g_Player.pos.x = g_Player.nextpos.x;
	g_Player.pos.y = g_Player.nextpos.y;
	g_Player.pos.z = g_Player.nextpos.z;






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


