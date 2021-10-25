#include "map.h"
#include "texture.h"
#include "sprite.h"
#include "polygon.h"
#include "player.h"


//****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//struct MAP_DATA_T
//{
//	D3DXVECTOR2 uv;		//UV�l
//	int			stop;	//�N���\�t���O(1�͐i���֎~)
//
//};
//
//MAP_DATA_T g_MapInfo[3] =
//{
//	{ { 0.25f,   0.0f}, 0},//�Ȃɂ��Ȃ�
//	{ {  0.0f, 0.625f}, 1},//��
//	{ {0.625f, 0.625f}, 1},//�؂芔
//};


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_map_test_01[4][10][20] = {
	{
		// 1�Ԏ�O
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}
    },
	{
		// ��O����2�Ԗ�
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}
	},
	{
		// ��O����3�Ԗ�
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}
	},
	{
		// ��O����4�Ԗ�
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1}
	}
};


int Tex_field000 = 0;
int Tex_field001 = 0;

static int g_Ground = 0;		// �w�i�p�e�N�X�`�����
static int g_CurrentPos = 0;	// ���݂̃}�b�v���W

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMap(void)
{
	g_Ground = LoadTexture("data/TEXTURE/basechip.png");

	Tex_field000 = LoadTexture("data/TEXTURE/field000.jpg");
	Tex_field001 = LoadTexture("data/TEXTURE/player.png");




	//// �Ă���
	//for (int i = 0; i < 3; i++)
	//{
	//	SetObject(2, Tex_field000, D3DXVECTOR3(0.0f + TEST01 * i, 0.0f + TEST01 * i, 0.0f + TEST01 * i),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(TEST01, TEST01, TEST01), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
	//		0.0f, 0.0f, 1.0f, 1.0f,
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	//}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMap(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMap(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMap(void)
{
	float offset_y;

	if (g_CurrentPos == 0)
		offset_y = 0.0f;
	else
		offset_y = -560.0f;




	for (int z = 0; z < MAP_Z_MAX; z++)
	{
		for (int y = 0; y < MAP_Y_MAX; y++)
		{
			for (int x = 0; x < MAP_X_MAX; x++)
			{
				switch (g_map_test_01[z][y][x])
				{
				case 0://�����\�����Ȃ�

					break;
				case 1://��
					// y��pos�̂Ƃ���( (MAP_Y_MAX - 1) - y)�����Ă���̂͒��g��10���̔z��ł�0~9�Ő����邸��̕␳
					SetObject(2, Tex_field000, D3DXVECTOR3(0.0f + (x * MAPCHIP_SIZE_X), 0.0f + (( (MAP_Y_MAX - 1) - y) * MAPCHIP_SIZE_Y), 0.0f + (z * MAPCHIP_SIZE_Z) ),
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(MAPCHIP_SIZE_X, MAPCHIP_SIZE_Y, MAPCHIP_SIZE_Z), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
						0.0f, 0.0f, 1.0f, 1.0f,
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
					break;
				}
			}
		}
	}


	//���C���[�O�̕\��
	//for (int y = 0; y < 14; y++)
	//{
	//	for (int x = 0; x < 12; x++)
	//	{
	//		switch (g_map_base[y][x])
	//		{
	//		case 0://����
	//			DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, 0.0f, 0.0f, 0.125f, 0.125f);
	//			break;
	//		case 1://��
	//			DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, 0.625f, 0.0f, 0.125f, 0.125f);
	//			break;
	//		}
	//	}
	//}

	////�w�i�I�u�W�F�N�g�̕\��
	//for (int y = 0; y < 14; y++)
	//{
	//	for (int x = 0; x < 12; x++)
	//	{
	//		MAP_DATA_T mapchip;
	//		mapchip = g_MapInfo[g_map_obj[y][x]];

	//		DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
	//	}
	//}
}

//int GetMapEnter(D3DXVECTOR2 pos)
//{
//	int x, y;
//	x = (int)(pos.x / 80.0f);//���W���}�b�v�`�b�v��̑傫���Ŋ���
//	y = (int)(pos.y / 80.0f);
//
//	return g_map_hitchk[g_CurrentPos][y][x];
//}

void SetCurrentMap(int next)
{
	g_CurrentPos = next;
}

int CheckBlockdata(int BlockX, int BlockY, int BlockZ)
{
	// BlockY�̂Ƃ���( (MAP_Y_MAX - 1) - BlockY)�����Ă���̂͒��g��10���̔z��ł�0~9�Ő����邸��̕␳
	int BlockData = 0;
	BlockData = g_map_test_01[BlockZ][(MAP_Y_MAX - 1) - BlockY][BlockX];

	return BlockData;
}

void ChangeBlockdata(int changenum, int BlockX, int BlockY, int BlockZ)
{
	g_map_test_01[BlockZ][(MAP_Y_MAX - 1) - BlockY][BlockX] = changenum;

	return ;
}

//int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
//{
//	int L1 = x1;      // ��
//	int R1 = x1 + w1; // �E(��+����)
//	int L2 = x2;      // ��
//	int R2 = x2 + w2; // �E(��+����)
//
//	if (R1 <= L2) return 0; //< �����������Ȃ����Ƃɂ���
//	if (R2 <= L1) return 0; //< �����������Ȃ����Ƃɂ���
//
//	int U1 = y1;      // ��
//	int D1 = y1 + h1; // ��(��+�c��)			// ������ӂ̃v���X�}�C�i�X�������������B
//	int U2 = y2;      // ��
//	int D2 = y2 + h2; // ��(��+�c��)
//
//	if (D1 <= U2) return 0; //<  �����������Ȃ����Ƃɂ���
//	if (D2 <= U1) return 0; //< �����������Ȃ����Ƃɂ���
//
//	// ����ȊO�̏ꍇ�͓������Ă���
//	return 1;
//}

bool CheckHit(D3DXVECTOR3 obj1_pos, D3DXVECTOR3 obj1_colsize, D3DXVECTOR3 obj2_pos, D3DXVECTOR3 obj2_colsize)
{
	float L1 = obj1_pos.x - (obj1_colsize.x / 2);		 // ��
	float R1 = obj1_pos.x + (obj1_colsize.x / 2);		 // �E
	float L2 = obj2_pos.x - (obj2_colsize.x / 2);		 // ��
	float R2 = obj2_pos.x + (obj2_colsize.x / 2);		 // �E

	if (R1 <= L2) return false; //< �����������Ȃ����Ƃɂ���
	if (R2 <= L1) return false; //< �����������Ȃ����Ƃɂ���

	float U1 = obj1_pos.y + (obj1_colsize.y / 2);       // ��
	float D1 = obj1_pos.y - (obj1_colsize.y / 2);		// ��(��+�c��) ������ӂ̃v���X�}�C�i�X�������������B
	float U2 = obj2_pos.y + (obj2_colsize.y / 2);       // ��
	float D2 = obj2_pos.y - (obj2_colsize.y / 2);		// ��(��+�c��)

	if (U1 <= D2) return false; //<  �����������Ȃ����Ƃɂ���
	if (U2 <= D1) return false; //< �����������Ȃ����Ƃɂ���

	float F1 = obj1_pos.z - (obj1_colsize.z / 2);		// ��O
	float B1 = obj1_pos.z + (obj1_colsize.z / 2);		// ��
	float F2 = obj2_pos.z - (obj2_colsize.z / 2);		// ��O
	float B2 = obj2_pos.z + (obj2_colsize.z / 2);		// ��

	if (B1 <= F2) return false; //<  �����������Ȃ����Ƃɂ���
	if (B2 <= F1) return false; //< �����������Ȃ����Ƃɂ���

	// ����ȊO�̏ꍇ�͓������Ă���
	return true;
}

bool CheckHitCircleBox
(D3DXVECTOR3 obj1_pos, float obj1_r, D3DXVECTOR3 obj2_pos, D3DXVECTOR3 obj2_colsize)
{
	PLAYER player = *GetPlayer();

	// �u���b�N��8���̍��W
	D3DXVECTOR3 LUF_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 RUF_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 LDF_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 RDF_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));

	D3DXVECTOR3 LUB_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 RUB_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 LDB_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
	D3DXVECTOR3 RDB_block = D3DXVECTOR3(obj2_pos.x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), obj2_pos.y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), obj2_pos.z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));

	// �~���g���������蔻��
	// �Ƃ肠����x��z�ł���Ă݂Ă� ���a�̓v���C���[�̓����蔻��̃T�C�Y�̂Ƃ肠����X(50.0f)���g��
	// �܂��~�̌��_�Ƃ����Е��̓_�̋��������߂�
	// �����Ƃ͕ʂ�x��z�̗����̍����o���Ă��� ���̎��Aobj2 - obj1�ƂȂ�悤�ɂ���B(obj1�̓����Ŕ�����s������)
	float radius = player.colsize.x / 2;

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

		float distance = CalculationDistance(player.nextpos.x, player.nextpos.z, Block_pos.x, Block_pos.z);
		D3DXVECTOR2 difference = D3DXVECTOR2(player.nextpos.x - Block_pos.x, player.nextpos.z - Block_pos.z);

		if (distance <= radius)
			return true;
	}

	// ����ȊO�̏ꍇ�͓������Ă��Ȃ�
	return false;
}


// 2�_�Ԃ̋��������߂�
float CalculationDistance(float obj1pos1, float obj1pos2, float obj2pos1, float obj2pos2)
{
		float distance = sqrt(pow(obj1pos1 - obj2pos1, 2) +
							  pow(obj1pos2 - obj2pos2, 2));
		return distance;
}

//// obj1 ���ꂼ���8�����v�Z�ŋ��߂�
//D3DXVECTOR3 obj1_LUF = D3DXVECTOR3(obj1_pos.x - (obj1_colsize.x / 2), obj1_pos.y + (obj1_colsize.y / 2), obj1_pos.z - (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_RUF = D3DXVECTOR3(obj1_pos.x + (obj1_colsize.x / 2), obj1_pos.y + (obj1_colsize.y / 2), obj1_pos.z - (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_LDF = D3DXVECTOR3(obj1_pos.x - (obj1_colsize.x / 2), obj1_pos.y - (obj1_colsize.y / 2), obj1_pos.z - (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_RDF = D3DXVECTOR3(obj1_pos.x + (obj1_colsize.x / 2), obj1_pos.y - (obj1_colsize.y / 2), obj1_pos.z - (obj1_colsize.z / 2));

//D3DXVECTOR3 obj1_LUB = D3DXVECTOR3(obj1_pos.x - (obj1_colsize.x / 2), obj1_pos.y + (obj1_colsize.y / 2), obj1_pos.z + (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_RUB = D3DXVECTOR3(obj1_pos.x + (obj1_colsize.x / 2), obj1_pos.y + (obj1_colsize.y / 2), obj1_pos.z + (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_LDB = D3DXVECTOR3(obj1_pos.x - (obj1_colsize.x / 2), obj1_pos.y - (obj1_colsize.y / 2), obj1_pos.z + (obj1_colsize.z / 2));
//D3DXVECTOR3 obj1_RDB = D3DXVECTOR3(obj1_pos.x + (obj1_colsize.x / 2), obj1_pos.y - (obj1_colsize.y / 2), obj1_pos.z + (obj1_colsize.z / 2));
//// obj2
//D3DXVECTOR3 obj2_LUF = D3DXVECTOR3(obj2_pos.x - (obj2_colsize.x / 2), obj2_pos.y + (obj2_colsize.y / 2), obj2_pos.z - (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_RUF = D3DXVECTOR3(obj2_pos.x + (obj2_colsize.x / 2), obj2_pos.y + (obj2_colsize.y / 2), obj2_pos.z - (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_LDF = D3DXVECTOR3(obj2_pos.x - (obj2_colsize.x / 2), obj2_pos.y - (obj2_colsize.y / 2), obj2_pos.z - (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_RDF = D3DXVECTOR3(obj2_pos.x + (obj2_colsize.x / 2), obj2_pos.y - (obj2_colsize.y / 2), obj2_pos.z - (obj2_colsize.z / 2));

//D3DXVECTOR3 obj2_LUB = D3DXVECTOR3(obj2_pos.x - (obj2_colsize.x / 2), obj2_pos.y + (obj2_colsize.y / 2), obj2_pos.z + (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_RUB = D3DXVECTOR3(obj2_pos.x + (obj2_colsize.x / 2), obj2_pos.y + (obj2_colsize.y / 2), obj2_pos.z + (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_LDB = D3DXVECTOR3(obj2_pos.x - (obj2_colsize.x / 2), obj2_pos.y - (obj2_colsize.y / 2), obj2_pos.z + (obj2_colsize.z / 2));
//D3DXVECTOR3 obj2_RDB = D3DXVECTOR3(obj2_pos.x + (obj2_colsize.x / 2), obj2_pos.y - (obj2_colsize.y / 2), obj2_pos.z + (obj2_colsize.z / 2));