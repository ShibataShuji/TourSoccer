//=============================================================================
//
// レンダラ [renderer.h]
// Author : KATSUMA MURASE
//
//=============================================================================
#pragma once

#include "main.h"

//*********************************************************
// 構造体
//*********************************************************

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//ブレンド無し
	BLEND_MODE_ALPHABLEND,	//αブレンド
	BLEND_MODE_ADD,			//加算ブレンド
	BLEND_MODE_SUBTRACT,	//減算ブレンド

	BLEDD_MODE_NUM
};

enum CULL_MODE 
{
	CULL_MODE_NONE,			//カリング無し
	CULL_MODE_FRONT,		//表のポリゴンを描画しない(CW)
	CULL_MODE_BACK,			//裏のポリゴンを描画しない(CCW)

	CULL_MODE_NUM
};

enum ADDRESS_MODE
{
	ADDRESS_MODE_WRAP,
	ADDRESS_MODE_MIRROR,
	ADDRESS_MODE_CLAMP,
	ADDRESS_MODE_BORDER,

	ADDRESS_MODE_NUM
};

enum FILTER_MODE
{
	FILTER_MODE_POINT,
	FILTER_MODE_LINEAR,
	FILTER_MODE_ANISOTROPIC,

	FILTER_MODE_NUM
};


// 頂点構造体
struct VERTEX_3D
{
    D3DXVECTOR3 Position;	// 頂点の座標
    D3DXVECTOR3 Normal;		// 法線(表に向かっての垂直な方向の線)(表はこっちだよ情報)(光の当たり方とかがかわる)
    D3DXCOLOR  Diffuse;		// 頂点の色の設定RGBA
    D3DXVECTOR2 TexCoord;	// UV値
};
// ライトの設定はレンダーcppの615行目くらい


// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16bit境界用
};


// ライト構造体
struct LIGHT {
	D3DXVECTOR4 Direction;       /* Direction in world space */
	D3DXCOLOR	Diffuse;         /* Diffuse color of light */
	D3DXCOLOR   Ambient;         /* Ambient color of light */
	int			Mode;
	int			Dummy[3];//16bit境界用
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

void Clear(void);
void Present(void);

ID3D11Device *GetDevice( void );
ID3D11DeviceContext *GetDeviceContext( void );

void SetDepthEnable( bool Enable );
void SetBlendState(BLEND_MODE bm);
void SetCullingMode(CULL_MODE cm);
void SetLightEnable(BOOL flag);
void SetAlphaTestEnable(BOOL flag);
void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am);
void SetSamplerBorderColor(D3DXCOLOR col);

void SetWorldViewProjection2D( void );
void SetWorldMatrix( D3DXMATRIX *WorldMatrix );
void SetViewMatrix( D3DXMATRIX *ViewMatrix );
void SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix );

void SetMaterial( MATERIAL Material );
void SetLight(LIGHT Light);
