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
		ColX = 0;
	if (g_Player.move.y < 0.0f)		// �v���C���[�͉��ɐi��ł���
		ColX = 1;
	if (g_Player.move.z > 0.0f)		// �v���C���[�͉��ɐi��ł���
		ColX = 0;
	if (g_Player.move.z < 0.0f)		// �v���C���[�͎�O�ɐi��ł���
		ColX = 1;

	// �������Ă���͈͂̃u���b�N���瓖���蔻��̂���u���b�N���ǂ������}�b�v�`�b�v���璲�ׂ�
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
					//ChangeBlockdata(2, x, y, z);
					// D3DXVECTOR3
					// �אڂ��Ă���u���b�N�� 1, �����蔻��̂���u���b�N���ƕ��������̂ŁA�X�ɍׂ��������蔻�������
					if (CheckHit(g_Player.nextpos, g_Player.colsize,
						D3DXVECTOR3(x * MAPCHIP_SIZE_X, y * MAPCHIP_SIZE_Y, z * MAPCHIP_SIZE_Z), D3DXVECTOR3(MAPCHIP_SIZE_X, MAPCHIP_SIZE_Y, MAPCHIP_SIZE_Z)))
					{
						// �v���C���[�ƃu���b�N�̐ڂ��Ă��钷����x,y,z���W�̂��ꂼ��Œ��ׂčł������Ƃ��낪�����蔻�肪���邱�Ƃɂ���
						float ContactLengthX = -1.0f;		// �����͕K�����̐��ɂȂ�̂ŕ��̐����Ɛڂ��Ă��Ȃ����ƂɂȂ�
						float ContactLengthY = -1.0f;
						float ContactLengthZ = -1.0f;
						float ContactLengthStart = 0.0f;	// �u���b�N�Ɛڂ��Ă�����W�̍�,��,��O�̍��W
						float ContactLengthFinish = 0.0f;	// �u���b�N�Ɛڂ��Ă�����W�̉E,��,���̍��W
						// x�̐ڂ��Ă��钷��
						ContactLengthStart = (x * MAPCHIP_SIZE_X) - (MAPCHIP_SIZE_X / 2);	// ���[,�����l�̓u���b�N�̒������̂܂�
						ContactLengthFinish = (x * MAPCHIP_SIZE_X) + (MAPCHIP_SIZE_X / 2);	// �E�[
						if (ContactLengthStart < g_Player.nextpos.x - (g_Player.colsize.x / 2))		// �X�^�[�g�n�_(�u���b�N�̍��[)���v���C���[�̍��[��菬������΃v���C���[�̍��[���X�^�[�g�n�_�Ƃ���
							ContactLengthStart = g_Player.nextpos.x - (g_Player.colsize.x / 2);
						if (ContactLengthFinish > g_Player.nextpos.x + (g_Player.colsize.x / 2))		// �X�^�[�g�n�_(�u���b�N�̍��[)���v���C���[�̉E�[���傫����΃v���C���[�̉E�[���t�B�j�b�V���n�_�Ƃ���
							ContactLengthFinish = g_Player.nextpos.x + (g_Player.colsize.x / 2);
						// �Ŋ��Ƀt�B�j�b�V��(�E�[)����X�^�[�g(���[)���Ђ��Ɛڂ��Ă��钷�������߂���
						ContactLengthX = ContactLengthFinish - ContactLengthStart;
						// y�̐ڂ��Ă��钷��
						ContactLengthStart = (y * MAPCHIP_SIZE_Y) - (MAPCHIP_SIZE_Y / 2);	// ���[,�����l�̓u���b�N�̒������̂܂�
						ContactLengthFinish = (y * MAPCHIP_SIZE_Y) + (MAPCHIP_SIZE_Y / 2);	// ��[
						if (ContactLengthStart < g_Player.nextpos.y - (g_Player.colsize.y / 2))
							ContactLengthStart = g_Player.nextpos.y - (g_Player.colsize.y / 2);
						if (ContactLengthFinish > g_Player.nextpos.y + (g_Player.colsize.y / 2))
							ContactLengthFinish = g_Player.nextpos.y + (g_Player.colsize.y / 2);
						// �Ŋ��Ƀt�B�j�b�V������X�^�[�g���Ђ��Ɛڂ��Ă��钷�������߂���
						ContactLengthY = ContactLengthFinish - ContactLengthStart;
						// Z�̐ڂ��Ă��钷��
						ContactLengthStart = (z * MAPCHIP_SIZE_Z) - (MAPCHIP_SIZE_Z / 2);	// �O�[,�����l�̓u���b�N�̒������̂܂�
						ContactLengthFinish = (z * MAPCHIP_SIZE_Z) + (MAPCHIP_SIZE_Z / 2);	// ���[
						if (ContactLengthStart < g_Player.nextpos.z - (g_Player.colsize.z / 2))
							ContactLengthStart = g_Player.nextpos.z - (g_Player.colsize.z / 2);
						if (ContactLengthFinish > g_Player.nextpos.z + (g_Player.colsize.z / 2))
							ContactLengthFinish = g_Player.nextpos.z + (g_Player.colsize.z / 2);
						// �Ŋ��Ƀt�B�j�b�V������X�^�[�g���Ђ��Ɛڂ��Ă��钷�������߂���
						ContactLengthZ = ContactLengthFinish - ContactLengthStart;

						// x,y,z,3�̐ڂ��Ă��钷������1�Ԓ������̂�I�o����
						int BestContact = 0;					// 0:x,1:y,2:z
						if (ContactLengthX < ContactLengthY)
						{
							if (ContactLengthY < ContactLengthZ)
								BestContact = 2;
							else
								BestContact = 1;
						}
						else
						{
							if (ContactLengthX < ContactLengthZ)
								BestContact = 2;
							else
								BestContact = 0;
						}

						// BestContact��move�ɂ��ColX,ColY,ColZ���痧���̂̂ǂ̖ʂƓ������Ă���̂������߂�
						int ColSurface = -1;				// ColSurface�̓T�C�R���̂ǂ̖ʂ�`�����B0:����,1:��둤,2:�㑤,3:����,4:�E��,5:����
						switch (BestContact)
						{
						case 0:
							if (ColX == 0)
								ColSurface = 5;
							if (ColX == 1)
								ColSurface = 4;
							break;
						case 1:
							if (ColY == 0)
								ColSurface = 3;
							if (ColY == 1)
								ColSurface = 2;
							break;
						case 2:
							if (ColZ == 0)
								ColSurface = 0;
							if (ColZ == 1)
								ColSurface = 1;
							break;
						}

						// �������Ă���ʂ���v���C���[�̍��W���C������
						switch (ColSurface)
						{
						case 0:
							g_Player.nextpos.z = (z * MAPCHIP_SIZE_Z) - (MAPCHIP_SIZE_Z / 2) - (g_Player.colsize.z / 2);
							ChangeBlockdata(2, x, y, z);
							break;
						case 1:
							g_Player.nextpos.z = (z * MAPCHIP_SIZE_Z) + (MAPCHIP_SIZE_Z / 2) + (g_Player.colsize.z / 2);
							ChangeBlockdata(2, x, y, z);
							break;
						case 2:
							g_Player.nextpos.y = (y * MAPCHIP_SIZE_Y) + (MAPCHIP_SIZE_Y / 2) + (g_Player.colsize.y / 2);
							ChangeBlockdata(2, x, y, z);
							break;
						case 3:
							g_Player.nextpos.y = (y * MAPCHIP_SIZE_Y) - (MAPCHIP_SIZE_Y / 2) - (g_Player.colsize.y / 2);
							ChangeBlockdata(2, x, y, z);
							break;
						case 4:
							g_Player.nextpos.x = (x * MAPCHIP_SIZE_X) + (MAPCHIP_SIZE_X / 2) + (g_Player.colsize.x / 2);
							//ChangeBlockdata(2, x, y, z);
							break;
						case 5:
							g_Player.nextpos.x = (x * MAPCHIP_SIZE_X) - (MAPCHIP_SIZE_X / 2) - (g_Player.colsize.x / 2);
							//ChangeBlockdata(2, x, y, z);
							break;
						}
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


