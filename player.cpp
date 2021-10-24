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

	// マップとの当たり判定
	// nextposの時の座標を8隅を計算で求める,当たり判定なのでsizeではなくcolsizeを使う
	D3DXVECTOR3 LUF = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUF = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDF = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDF = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z - (g_Player.colsize.z / 2));

	D3DXVECTOR3 LUB = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUB = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y + (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDB = D3DXVECTOR3(g_Player.nextpos.x - (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDB = D3DXVECTOR3(g_Player.nextpos.x + (g_Player.colsize.x / 2), g_Player.nextpos.y - (g_Player.colsize.y / 2), g_Player.nextpos.z + (g_Player.colsize.z / 2));

	// 8隅の座標を使い、マップのどのブロックからどのブロックまでを検索にかけるか計算する,intで小数点以下切り捨てされる
	int Block_Left  = (LUF.x - (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;			// 左端
	int Block_Right = (RUF.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X + 1;		// 右端,小数点以下切り捨てされるので+1する
	int Block_Up    = (LUF.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y + 1;		// 上端,小数点以下切り捨てされるので+1する
	int Block_Down  = (LUB.y - (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;		// 下端,小数点以下切り捨てされるので+1する
	int Block_Front = (LUF.z - (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;			// 前端
	int Block_Back  = (LUB.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z + 1;		// 奥端,小数点以下切り捨てされるので+1する

	// +1したときにマップの最大値から溢れないようにする
	if (Block_Right >= MAP_X_MAX)
		Block_Right = MAP_X_MAX - 1;
	if (Block_Up >= MAP_Y_MAX)
		Block_Up = MAP_Y_MAX - 1;
	if (Block_Back >= MAP_Z_MAX)
		Block_Back = MAP_Z_MAX - 1;


	// moveからどの面が当たることが予想されるかを計算する,動いていないと計算の対象外にする
	int ColX = -1;		// moveから面のどちらが当たっているかを調べる,-1:判定を行わない,0:左,1:右
	int ColY = -1;		// moveから面のどちらが当たっているかを調べる,-1:判定を行わない,0:下,1:上
	int ColZ = -1;		// moveから面のどちらが当たっているかを調べる,-1:判定を行わない,0:前,1:奥
	if (g_Player.move.x > 0.0f)		// プレイヤーは右に進んでいる
		ColX = 0;
	if (g_Player.move.x < 0.0f)		// プレイヤーは左に進んでいる
		ColX = 1;
	if (g_Player.move.y > 0.0f)		// プレイヤーは上に進んでいる
		ColX = 0;
	if (g_Player.move.y < 0.0f)		// プレイヤーは下に進んでいる
		ColX = 1;
	if (g_Player.move.z > 0.0f)		// プレイヤーは奥に進んでいる
		ColX = 0;
	if (g_Player.move.z < 0.0f)		// プレイヤーは手前に進んでいる
		ColX = 1;

	// 当たっている範囲のブロックから当たり判定のあるブロックかどうかをマップチップから調べる
	for (int z = Block_Front; z <= Block_Back; z++)
	{
		for (int y = Block_Down; y <= Block_Up; y++)
		{
			for (int x = Block_Left; x <= Block_Right; x++)
			{
				// そのブロックが当たり判定があるブロックかどうか調べる
				int BlockData = CheckBlockdata(x, y, z);
				// そのブロックデータが 1 だったら当たり判定があるので中で当たり判定の計算し、当たっている面を1面に決める
				if (BlockData == 1)
				{
					//ChangeBlockdata(2, x, y, z);
					// D3DXVECTOR3
					// 隣接しているブロックが 1, 当たり判定のあるブロックだと分かったので、更に細かく当たり判定を見る
					if (CheckHit(g_Player.nextpos, g_Player.colsize,
						D3DXVECTOR3(x * MAPCHIP_SIZE_X, y * MAPCHIP_SIZE_Y, z * MAPCHIP_SIZE_Z), D3DXVECTOR3(MAPCHIP_SIZE_X, MAPCHIP_SIZE_Y, MAPCHIP_SIZE_Z)))
					{
						// プレイヤーとブロックの接している長さをx,y,z座標のそれぞれで調べて最も長いところが当たり判定があることにする
						float ContactLengthX = -1.0f;		// 長さは必ず正の数になるので負の数だと接していないことになる
						float ContactLengthY = -1.0f;
						float ContactLengthZ = -1.0f;
						float ContactLengthStart = 0.0f;	// ブロックと接している座標の左,下,手前の座標
						float ContactLengthFinish = 0.0f;	// ブロックと接している座標の右,上,奥の座標
						// xの接している長さ
						ContactLengthStart = (x * MAPCHIP_SIZE_X) - (MAPCHIP_SIZE_X / 2);	// 左端,初期値はブロックの長さそのまま
						ContactLengthFinish = (x * MAPCHIP_SIZE_X) + (MAPCHIP_SIZE_X / 2);	// 右端
						if (ContactLengthStart < g_Player.nextpos.x - (g_Player.colsize.x / 2))		// スタート地点(ブロックの左端)がプレイヤーの左端より小さければプレイヤーの左端をスタート地点とする
							ContactLengthStart = g_Player.nextpos.x - (g_Player.colsize.x / 2);
						if (ContactLengthFinish > g_Player.nextpos.x + (g_Player.colsize.x / 2))		// スタート地点(ブロックの左端)がプレイヤーの右端より大きければプレイヤーの右端をフィニッシュ地点とする
							ContactLengthFinish = g_Player.nextpos.x + (g_Player.colsize.x / 2);
						// 最期にフィニッシュ(右端)からスタート(左端)をひくと接している長さが求められる
						ContactLengthX = ContactLengthFinish - ContactLengthStart;
						// yの接している長さ
						ContactLengthStart = (y * MAPCHIP_SIZE_Y) - (MAPCHIP_SIZE_Y / 2);	// 下端,初期値はブロックの長さそのまま
						ContactLengthFinish = (y * MAPCHIP_SIZE_Y) + (MAPCHIP_SIZE_Y / 2);	// 上端
						if (ContactLengthStart < g_Player.nextpos.y - (g_Player.colsize.y / 2))
							ContactLengthStart = g_Player.nextpos.y - (g_Player.colsize.y / 2);
						if (ContactLengthFinish > g_Player.nextpos.y + (g_Player.colsize.y / 2))
							ContactLengthFinish = g_Player.nextpos.y + (g_Player.colsize.y / 2);
						// 最期にフィニッシュからスタートをひくと接している長さが求められる
						ContactLengthY = ContactLengthFinish - ContactLengthStart;
						// Zの接している長さ
						ContactLengthStart = (z * MAPCHIP_SIZE_Z) - (MAPCHIP_SIZE_Z / 2);	// 前端,初期値はブロックの長さそのまま
						ContactLengthFinish = (z * MAPCHIP_SIZE_Z) + (MAPCHIP_SIZE_Z / 2);	// 奥端
						if (ContactLengthStart < g_Player.nextpos.z - (g_Player.colsize.z / 2))
							ContactLengthStart = g_Player.nextpos.z - (g_Player.colsize.z / 2);
						if (ContactLengthFinish > g_Player.nextpos.z + (g_Player.colsize.z / 2))
							ContactLengthFinish = g_Player.nextpos.z + (g_Player.colsize.z / 2);
						// 最期にフィニッシュからスタートをひくと接している長さが求められる
						ContactLengthZ = ContactLengthFinish - ContactLengthStart;

						// x,y,z,3つの接している長さから1番長いものを選出する
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

						// BestContactとmoveによるColX,ColY,ColZから立方体のどの面と当たっているのかを求める
						int ColSurface = -1;				// ColSurfaceはサイコロのどの面を描くか。0:正面,1:後ろ側,2:上側,3:下側,4:右側,5:左側
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

						// 当たっている面からプレイヤーの座標を修正する
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



	// 当たり判定等の計算をnextposで行ったあと最後にposに反映させる
	g_Player.pos.x = g_Player.nextpos.x;
	g_Player.pos.y = g_Player.nextpos.y;
	g_Player.pos.z = g_Player.nextpos.z;

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


