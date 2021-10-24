//=============================================================================
//
// �n�ʏ��� [polygon.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct POLYGON
{
	D3DXVECTOR3		pos;		// �|���S���̈ʒu
	D3DXVECTOR3		rot;		// �|���S���̌���(��])
	D3DXVECTOR3		scl;		// �|���S���̑傫��(�X�P�[��)

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};

struct OBJECT
{
	POLYGON g_Polygon;

	D3DXVECTOR3 size;

	int g_Tex;

};

struct OBJECTDATA
{

	D3DXVECTOR3		pos;		// �|���S���̈ʒu
	D3DXVECTOR3		rot;		// �|���S���̌���(��])(x�ŉ���,y�ŉE��,z�Ŏ��v�̐j�̂悤��,��6.28��360�x,��1.57��90�x
	D3DXVECTOR3		size;		// �傫��
	D3DXVECTOR3		scl;		// �傫���̔{��

	int				g_Tex;		// �e�N�X�`��
	int				act;		// �ǂ�������Ԃ�(�A�j���[�V�����Ƃ��̎��g��)

	int				arraynum;	// �|���S���̔z��Ŏg����ŏ��̔ԍ� 6n

	int				DisappearanceCount;	// ������܂ł̃t���[���̃J�E���g -1�ɐݒ肷��Ɩ���
	bool			isUse;		// �g���Ă��邩�ǂ���

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

void ReleasePolygon(void);

void DrawPolygonObjectCenter(int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Size,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, D3DXVECTOR3 Rot,
	bool UseNormal, D3DXVECTOR3 Normal);
void DrawPolygonObjectLeftTop();


// surface�̓T�C�R���̂ǂ̖ʂ�`���܂����B0:����,1:��둤,2:�㑤,3:����,4:�E��,5:����
void SetObject(int surface, int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color,
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count);

void SetObjectLeftUp(int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color,
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count);