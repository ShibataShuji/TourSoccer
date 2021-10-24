//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "texture.h"
#include "sprite.h"
#include "polygon.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(16)	// �L�����T�C�Y
#define TEXTURE_HEIGHT				(32)	// 


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static bool						g_Use;						// true:�g���Ă���  false:���g�p
static float					g_w, g_h;					// ���ƍ���
static D3DXVECTOR3				g_Pos;						// �|���S���̍��W
static int						g_TexNo;					// �e�N�X�`���ԍ�

static int						g_Score;					// �X�R�A

int				g_Score1;
int				g_Score2;
int				g_Score3;
int				g_Score4;
int				g_Score5;
int				g_Score6;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	//�e�N�X�`������
	g_TexNo = LoadTexture("data/TEXTURE/number.png");

	//������
	g_Use   = true;
	g_w     = TEXTURE_WIDTH;
	g_h     = TEXTURE_HEIGHT;
	g_Pos   = D3DXVECTOR3(100.0f, 20.0f, 0.0f);

	g_Score = 0;	// �X�R�A�̏�����
	g_Score1 = 0;
	g_Score2 = 0;
	g_Score3 = 0;
	g_Score4 = 0;
	g_Score5 = 0;
	g_Score6 = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	PLAYER player = *GetPlayer();

	//�L�����t���O��ON�Ȃ�`�悷��
	if (g_Use)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));

		// ��������������
		int number = g_Score;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number /= 10;
		}


		// �X�R�A�P
		int number1 = g_Score1;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number1 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 1;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number1 /= 10;
		}

		// �X�R�A�Q
		int number2 = g_Score2;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number2 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 2;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number2 /= 10;
		}

		// �X�R�A�R
		int number3 = g_Score3;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number3 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 3;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number3 /= 10;
		}

		// �X�R�A�S
		int number4 = g_Score4;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number4 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 4;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number4 /= 10;
		}

		// �X�R�A�T
		int number5 = g_Score5;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number5 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 5;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number5 /= 10;
		}

		// �X�R�A�U
		int number6 = g_Score6;
		for (int i = 0; i < SCORE_DIGIT; i++)
		{
			// ����\�����錅�̐���
			float x = (float)(number6 % 10);

			// �X�R�A�̈ʒu��e�N�X�`���[���W�𔽉f
			float px = g_Pos.x - g_w * i;	// �v���C���[�̕\���ʒuX
			float py = g_Pos.y - 40.0f * 6;			// �v���C���[�̕\���ʒuY
			float pw = g_w;				// �v���C���[�̕\����
			float ph = g_h;				// �v���C���[�̕\������

			float tw = 1.0f / 10;		// �e�N�X�`���̕�
			float th = 1.0f / 1;		// �e�N�X�`���̍���
			float tx = x * tw;			// �e�N�X�`���̍���X���W
			float ty = 0.0f;			// �e�N�X�`���̍���Y���W

			D3DXVECTOR3 pos = D3DXVECTOR3(px, py, -20.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 size = D3DXVECTOR3(pw, ph, 0.0f);
			D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetObject(0, g_TexNo, pos, rot, size, scl,
				tx, ty, tw, th,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

			// ���̌���
			number6 /= 10;
		}
	}
}

//=============================================================================
// �X�R�A�����Z����
// ����:add :�ǉ�����_���B�}�C�i�X���\
//=============================================================================
void AddScore(int add)
{
	g_Score += add;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

void SetScore(int score)
{
	g_Score = score;

	if (g_Score > SCORE_MAX)
	{
		g_Score = SCORE_MAX;
	}
}

void SetScore1(int score)
{
	g_Score1 = score;

	if (g_Score1 > SCORE_MAX)
	{
		g_Score1 = SCORE_MAX;
	}
}

void SetScore2(int score)
{
	g_Score2 = score;

	if (g_Score2 > SCORE_MAX)
	{
		g_Score2 = SCORE_MAX;
	}
}

void SetScore3(int score)
{
	g_Score3 = score;

	if (g_Score3 > SCORE_MAX)
	{
		g_Score3 = SCORE_MAX;
	}
}

void SetScore4(int score)
{
	g_Score4 = score;

	if (g_Score4 > SCORE_MAX)
	{
		g_Score4 = SCORE_MAX;
	}
}

void SetScore5(int score)
{
	g_Score5 = score;

	if (g_Score5 > SCORE_MAX)
	{
		g_Score5 = SCORE_MAX;
	}
}

void SetScore6(int score)
{
	g_Score6 = score;

	if (g_Score6 > SCORE_MAX)
	{
		g_Score6 = SCORE_MAX;
	}
}