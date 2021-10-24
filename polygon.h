//=============================================================================
//
// 地面処理 [polygon.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct POLYGON
{
	D3DXVECTOR3		pos;		// ポリゴンの位置
	D3DXVECTOR3		rot;		// ポリゴンの向き(回転)
	D3DXVECTOR3		scl;		// ポリゴンの大きさ(スケール)

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
};

struct OBJECT
{
	POLYGON g_Polygon;

	D3DXVECTOR3 size;

	int g_Tex;

};

struct OBJECTDATA
{

	D3DXVECTOR3		pos;		// ポリゴンの位置
	D3DXVECTOR3		rot;		// ポリゴンの向き(回転)(xで奥に,yで右左,zで時計の針のように,約6.28で360度,約1.57で90度
	D3DXVECTOR3		size;		// 大きさ
	D3DXVECTOR3		scl;		// 大きさの倍率

	int				g_Tex;		// テクスチャ
	int				act;		// どういう状態か(アニメーションとかの時使う)

	int				arraynum;	// ポリゴンの配列で使われる最初の番号 6n

	int				DisappearanceCount;	// 消えるまでのフレームのカウント -1に設定すると無限
	bool			isUse;		// 使われているかどうか

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス

};


//*****************************************************************************
// プロトタイプ宣言
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


// surfaceはサイコロのどの面を描きますか。0:正面,1:後ろ側,2:上側,3:下側,4:右側,5:左側
void SetObject(int surface, int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color,
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count);

void SetObjectLeftUp(int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color,
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count);