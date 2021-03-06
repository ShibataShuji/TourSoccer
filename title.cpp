//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
//#include "sound.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_TextureNo = 0;	// テクスチャ情報
//static int	g_BGMNo = 0;		// BGM識別子

								//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	//テクスチャ生成
	g_TextureNo = LoadTexture("data/TEXTURE/title.png");

	//g_BGMNo = LoadSound("data/BGM/sample000.wav");

	//255(-1)をループ指定すると無限ループ
	//PlaySound(g_BGMNo, -1);

	SetObject(0, g_TextureNo, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);

	SetObject(0, g_TextureNo, D3DXVECTOR3((SCREEN_WIDTH / 2) - 0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(100.0f, 100.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	UninitPolygon();
	//StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	/*DrawSpriteLeftTop(g_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);*/

}

