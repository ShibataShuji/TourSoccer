/*==============================================================================

   頂点管理 [player.cpp]
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
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER g_Player;
static int g_ShotSENo = 0;

static float g_CharaUV = 0.0f;
static int g_AnimePtn = 0;
static int g_AnimeWaitFrame = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{

	//
	//g_ShotSENo = LoadSound("data/SE/shot000.wav");

	// テクスチャ生成
	g_Player.texNo = LoadTexture("data/TEXTURE/player.png");

	// 位置・回転・スケールの初期設定
	g_Player.size	 = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);							// 配置の大きさ
	g_Player.colsize = D3DXVECTOR3(PLAYER_COL_SIZE_X, PLAYER_COL_SIZE_Y, PLAYER_COL_SIZE_Z);							// 当たり判定の大きさ
	g_Player.pos     = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 配置する座標
	g_Player.oldpos  = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 前のフレームの座標を保存
	g_Player.nextpos = D3DXVECTOR3(0.0f, (MAPCHIP_SIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 次のフレームの座標の計算で使用
	g_Player.drawpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 配置する座標
	g_Player.rot     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 配置の角度
	g_Player.scl     = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// 大きさの倍率

	g_Player.move    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動の力

	g_Player.act = 0;

	g_Player.ground = true;

	g_Player.isUse = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{

	// oldposの設定
	g_Player.oldpos = g_Player.pos;


	// move移動の力の設定(アップデートの最初に書くといいかも)(0.0fに近づけていく)
	float friction;					// 摩擦力,抵抗力(床とか空中とかそういうのによって変更する)
	float AirResistance;			// 空気抵抗
	float max_fall_speed = 8.0f;	// 落下による最大速度
	friction = 0.3f;
	AirResistance = 0.15f;
		// xの設定
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
		// yの設定
		// 地面にいる状態であれば
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
		g_Player.move.y = 0.0f;		// 地面にいるからこれでいいかも
	}
	else
	{
		// 地面にいない状態であれば
		g_Player.move.y = g_Player.move.y - AirResistance;
		if (g_Player.move.y < -max_fall_speed)
			g_Player.move.y = -max_fall_speed;
	}
		// zの設定
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


	// キー入力による移動の設定
	// 他のなにかによってキー入力による最大スピードを超えていてもキー入力による最大スピードにリセットされないようにしてる
	float max_speed_for_kye = 4.0f;

	if (GetKeyboardPress(DIK_UP))
	{
			// g_Player.pos.z -= 1.0f;
			
			if (g_Player.move.z < max_speed_for_kye)
			{
				// キー入力による最大スピードになるように調整,それを超えることはないようにする。差を足す
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
			// キー入力による最大スピードになるように調整,それを超えることはないようにする。差を足す
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
			// キー入力による最大スピードになるように調整,それを超えることはないようにする。差を足す
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
			// キー入力による最大スピードになるように調整,それを超えることはないようにする。差を足す
			if (g_Player.move.x > max_speed_for_kye - 1.0f)
			{
				g_Player.move.x += max_speed_for_kye - g_Player.move.x;
			}
			else
				g_Player.move.x += 1.0f;
		}

	}


	// moveによる移動をnextpos座標に適用させる
	g_Player.nextpos.x += g_Player.move.x;
	g_Player.nextpos.y += g_Player.move.y;
	g_Player.nextpos.z += g_Player.move.z;

	// surfaceはサイコロのどの面を描きますか。0:正面,1:後ろ側,2:上側,3:下側,4:右側,5:左側

	// nextposを使って当たり判定の計算をする,最終的にposにnextposを適用する
	// ①nextposからプレイヤーが今どの




	////マップ1へ切り替える
	//if (GetKeyboardTrigger(DIK_L))
	//{
	//	SetCurrentMap(1);
	//}
	////マップ0へ切り替える
	//if (GetKeyboardTrigger(DIK_K))
	//{
	//	SetCurrentMap(0);
	//}


	//// 弾発射
	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	PlaySound(g_ShotSENo, 0);

	//	SetVolume(g_ShotSENo, 0.1f);

	//	D3DXVECTOR2 pos = g_Player.pos;
	//	SetBullet(pos);		// １発目
	//	AddScore(123);
	//}

	//歩きアニメーション
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
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	// pos を drawpos に変換する処理
	// 今はまだマップが実装されてないからそのまま。
	g_Player.drawpos = g_Player.pos;

	SetScore(g_Player.drawpos.x);

	// 毎フレーム更新するので最期の消えるカウントは 1 
	SetObject(0, g_Player.texNo, g_Player.drawpos, g_Player.rot, g_Player.size, g_Player.scl,
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
}

//=============================================================================
// プレイヤー構造体の先頭アドレスを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}


