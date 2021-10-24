//=============================================================================
//
// �|���S���\������ [polygon.cpp]
// Author : 
//
//=============================================================================
#include <string.h>
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX		(1)							// �e�N�X�`���̐�

#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

#define	SIZE_X			(200.0f)					// �n�ʂ̃T�C�Y(X����)
#define SIZE_Y          (100.0f)					// �n�ʂ̃T�C�Y(Y����)
#define	SIZE_Z			(100.0f)					// �n�ʂ̃T�C�Y(Z����)

#define VERTEX_NUM       (1200)

#define OBJECT_NUM       (199)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPolygon(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_���

static OBJECT g_Object[OBJECT_NUM];


static OBJECTDATA g_ObjectData[OBJECT_NUM];

int creatcooltime;


// ���_�z��
static VERTEX_3D g_VertexArray[VERTEX_NUM] = {
	//�V��1
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	//��6
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	//�E����2
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	//������5
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	//������3
	{D3DXVECTOR3( SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	//��O����4
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3 (SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},


};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	creatcooltime = 0;


	// ���_�o�b�t�@�̍쐬
	MakeVertexPolygon();


	// �I�u�W�F�N�g�f�[�^�\���̂̏�����
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		// �e�N�X�`������
		g_ObjectData[i].g_Tex = LoadTexture("data/TEXTURE/saikoro_2x3.png");

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_ObjectData[i].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �z�u������W
		g_ObjectData[i].rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �z�u�̊p�x
		g_ObjectData[i].size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	// �z�u�̊p�x
		g_ObjectData[i].scl  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �傫���̔{��

		g_ObjectData[i].act = 0;
		g_ObjectData[i].arraynum = 0;
		g_ObjectData[i].DisappearanceCount = -1;
		g_ObjectData[i].isUse = false;

		// g_ObjectData[i].mtxWorld;	// ���[���h�}�g���b�N�X(�悭�킩���ĂȂ�)
	}

	int texnoo = LoadTexture("data/TEXTURE/field000.jpg");

	SetObject(0, texnoo, D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{

	// �S�ẴI�u�W�F�N�g�f�[�^���g���Ă��Ȃ���Ԃɂ���
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if(g_ObjectData[i].isUse == true)
			g_ObjectData[i].isUse = false;
	}

	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void ReleasePolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	PLAYER player = *GetPlayer();

	if (creatcooltime >= 0)
		creatcooltime--;

	CAMERA *cam = GetCamera();

	for (int i = 0; i < OBJECT_NUM; i++)
	{

		//// ��]�������Ⴄ
		//if (GetKeyboardPress(DIK_LEFT))
		//{
		//	// g_ObjectData[i].rot.y -= VALUE_ROTATE;
		//	if (creatcooltime < 0)
		//	{
		//		creatcooltime = 60;
		//		SceneFadeIn(SCENE_TITLE);

		//		int texnoo = LoadTexture("data/TEXTURE/saikoro_2x3.png");
		//		SetObject(texnoo, D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//			D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		//			0.0f, 0.0f, 1.0f, 1.0f,
		//			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//			false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);
		//	}
		//}
		//if (GetKeyboardPress(DIK_RIGHT))
		//{
		//	//g_ObjectData[i].rot.y += VALUE_ROTATE;

		//	if (creatcooltime < 0)
		//	{
		//		creatcooltime = 60;
		//		int texnoo = LoadTexture("data/TEXTURE/field000.jpg");
		//		SetObject(texnoo, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//			D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		//			0.0f, 0.0f, 1.0f, 1.0f,
		//			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//			false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);
		//	}


		//}
		//if (GetKeyboardPress(DIK_UP))
		//{
		//	g_ObjectData[i].rot.x -= VALUE_ROTATE;
		//}
		//if (GetKeyboardPress(DIK_DOWN))
		//{
		//	g_ObjectData[i].rot.x += VALUE_ROTATE;
		//}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_ObjectData[i].rot.y = g_ObjectData[i].rot.x = 0.0f;
		//}



		// �������|���S���̒��_�������������Ă�����x�X�V�����Ă����
		ReleasePolygon();
		// ���_�o�b�t�@�̍쐬
		MakeVertexPolygon();

#ifdef _DEBUG	// �f�o�b�O����\������
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_ObjectData[i].rot.x, g_ObjectData[i].rot.y);
		//sprintf(&str[strlen(str)], " posX:%.2f posY:%.2f", player.pos.x, player.pos.y);

#endif

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �g�p���Ă���̃f�[�^��T��
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if (g_ObjectData[i].isUse == true)		// �g�p���Ă���f�[�^��������
		{

			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ObjectData[i].g_Tex));


			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ObjectData[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_ObjectData[i].scl.x, g_ObjectData[i].scl.y, g_ObjectData[i].scl.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectData[i].rot.y, g_ObjectData[i].rot.x, g_ObjectData[i].rot.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_ObjectData[i].pos.x, g_ObjectData[i].pos.y, g_ObjectData[i].pos.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_ObjectData[i].mtxWorld);

			int startlocation = 6 * i + 0;

			// �|���S���`��(�`��Ɏg�����_�̐����w��)
			GetDeviceContext()->Draw(6, startlocation);


			// ���ŃJ�E���g��i�߂鏈���B-1�����Ă���0�ɂȂ�������ŁB���X-1�w��ȂǕ��̐��̏ꍇ����
			if (g_ObjectData[i].DisappearanceCount > 0)
				g_ObjectData[i].DisappearanceCount--;

			// ���ŃJ�E���g��0�ɂȂ�������ł�����
			if (g_ObjectData[i].DisappearanceCount == 0)
				g_ObjectData[i].isUse = false;
		}
	}


}

HRESULT MakeVertexPolygon(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUM;	// ���_�̐���������(���_�o�b�t�@)���m��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �O���[�o���̒��_�z�񂩂璸�_�o�b�t�@������
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}

void DrawPolygonObjectCenter(int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Size,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, D3DXVECTOR3 Rot,
	bool UseNormal, D3DXVECTOR3 Normal)
{

	//////// �@��(���̓���������g��Ȃ��Ȃ��)
	//////if (!UseNormal)
	//////{
	//////	// �{���̓��C�g�𖳎����Ă����Ɩ��邭���������Ǎ��̂Ƃ���킩��Ȃ�����
	//////	// �Ƃ肠�������̃��C�g�Ŗ��邢�ݒ�B
	//////	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//////}

	//////// ���[���h�}�e���b�N�X�̒�`(�悭�킩���ĂȂ��Ȃɂ���)
	//////D3DXMATRIX mtxWorld;

	//////// �X�P�[���̒�`�Ə�����(�����H)
	//////D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//////float LU = Pos.x - (Size.x / 2);
	//////float RU = Pos.x + (Size.x / 2);
	//////float LD = Pos.x + (Size.x / 2);

	//////// ��������I�u�W�F�N�g�̒[�����̍��W�����߂�
	//////// Left Rigt Up Down in Flont Behind
	//////D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));

	//////D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));


	//////// ���_�z��
	//////VERTEX_3D g_VertexArray_List[LIST_VERTEX_NUM] = {

	//////{D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V)},
	//////{D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V)},
	//////{D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH)},
	//////{D3DXVECTOR3(RUF.x, RUF.y, RUF.y), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V)},
	//////{D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH)},
	//////{D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH)},

	//////};


	//////// ���_�o�b�t�@����
	//////D3D11_BUFFER_DESC bd;
	//////ZeroMemory(&bd, sizeof(bd));
	//////bd.Usage = D3D11_USAGE_DYNAMIC;;
	//////bd.ByteWidth = sizeof(VERTEX_3D) * LIST_VERTEX_NUM;	// ���_�̐���������(���_�o�b�t�@)���m��
	//////bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//////bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//////// �O���[�o���̒��_�z�񂩂璸�_�o�b�t�@������
	//////D3D11_SUBRESOURCE_DATA sd;
	//////ZeroMemory(&sd, sizeof(sd));
	//////sd.pSysMem = g_VertexArray_List;

	//////GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);



	//////// ���_�o�b�t�@�ݒ�
	//////UINT stride = sizeof(VERTEX_3D);
	//////UINT offset = 0;
	//////GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//////// �v���~�e�B�u�g�|���W�ݒ�
	//////GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//////// �}�e���A���ݒ�
	//////MATERIAL material;
	//////ZeroMemory(&material, sizeof(material));
	//////material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//////SetMaterial(material);

	//////// �e�N�X�`���ݒ�
	//////GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));


	//////D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//////// ���[���h�}�g���b�N�X�̏�����
	//////D3DXMatrixIdentity(&mtxWorld);

	//////// �X�P�[���𔽉f
	//////D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//////// ��]�𔽉f
	//////D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, Rot.x, Rot.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//////// �ړ��𔽉f
	//////D3DXMatrixTranslation(&mtxTranslate, Pos.x, Pos.y, Pos.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//////// ���[���h�}�g���b�N�X�̐ݒ�
	//////SetWorldMatrix(&mtxWorld);

	//////// �|���S���`��(�`��Ɏg�����_�̐����w��)
	//////GetDeviceContext()->Draw(LIST_VERTEX_NUM, 0);

}

void DrawPolygonObjectLeftTop()
{

}

// surface�̓T�C�R���̂ǂ̖ʂ�`���܂����B0:����,1:��둤,2:�㑤,3:����,4:�E��,5:����
void SetObject(int surface, int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, 
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count)
{

	// ���g�p�̃f�[�^��T��
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if (g_ObjectData[i].isUse == false)		// ���g�p��Ԃ̃f�[�^��������
		{


			//// �@��(���̓���������g��Ȃ��Ȃ��)
			//if (!UseNormal)
			//{
			//	// �{���̓��C�g�𖳎����Ă����Ɩ��邭���������Ǎ��̂Ƃ���킩��Ȃ�����
			//	// �Ƃ肠�������̃��C�g�Ŗ��邢�ݒ�B
			//	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//}

			// �e�N�X�`������
			g_ObjectData[i].g_Tex = texNo;

			// �ʒu�E��]�E�X�P�[���̏����ݒ�
			g_ObjectData[i].pos  = Pos;		// �z�u������W
			g_ObjectData[i].rot  = Rot;		// �z�u�̊p�x
			g_ObjectData[i].scl  = Scl;		// �傫���̔{��
			g_ObjectData[i].size = Size;	// �傫��,���a

			g_ObjectData[i].act = 0;
			g_ObjectData[i].arraynum = 6 * i;
			g_ObjectData[i].DisappearanceCount = disappearance_count;
			g_ObjectData[i].isUse = true;		// �g�p����̂�true�ɂ���


			// �����̍��W�Ȃǂ���I�u�W�F�N�g�̃|���S����8���̋������̍��W�����߂�
			// Left Rigt Up Down in Flont Behind
			// ��肭�����Ȃ������v�Z���@��
			/*D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));

			D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));*/

			// ��肭�������v�Z���@��
			D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - Size.x, Pos.y + Size.y, Pos.z - Size.z);
			D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + Size.x, Pos.y + Size.y, Pos.z - Size.z);
			D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - Size.x, Pos.y - Size.y, Pos.z - Size.z);
			D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + Size.x, Pos.y - Size.y, Pos.z - Size.z);

			D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - Size.x, Pos.y + Size.y, Pos.z + Size.z);
			D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + Size.x, Pos.y + Size.y, Pos.z + Size.z);
			D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - Size.x, Pos.y - Size.y, Pos.z + Size.z);
			D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + Size.x, Pos.y - Size.y, Pos.z + Size.z);


			// ���_�z��̐ݒ�
			switch (surface) {
			case 0:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;

			case 1:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 2:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 3:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 4:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 5:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;


			}


			return;					// �Z�b�g�ł����̂ŏI������
		}
	}

	// ���g�p��Ԃ̃f�[�^��������Ȃ������炱���ɂ���̂ŃG���[�Ƃ��ċ����I��
	exit(1);

}