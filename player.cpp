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
#include <math.h>


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
	g_Player.pos     = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 配置する座標
	g_Player.oldpos  = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 前のフレームの座標を保存
	g_Player.nextpos = D3DXVECTOR3(0.0f, (MAPCHIP_COLSIZE_Y / 2) + (g_Player.size.y / 2), 0.0f);			// 次のフレームの座標の計算で使用
	g_Player.drawpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 配置する座標
	g_Player.rot     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 配置の角度
	g_Player.scl     = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// 大きさの倍率

	g_Player.move    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動の力

	g_Player.act = 0;

	g_Player.ground = true;

	g_Player.isUse = false;



	g_Player.OldBlock_RightEnd = 0;
	g_Player.OldBlock_UpEnd = 0;
	g_Player.OldBlock_BehindEnd = 0;

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

	// oldpos,oldblockの設定
	g_Player.oldpos = g_Player.pos;
	// posから今いるブロックはどこかを求める
	int oldblock_x = (g_Player.oldpos.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int oldblock_y = (g_Player.oldpos.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int oldblock_z = (g_Player.oldpos.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	// oldposの時の座標を8隅を計算で求める,当たり判定なのでsizeではなくcolsizeを使う
	D3DXVECTOR3 LUFold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUFold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDFold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDFold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z - (g_Player.colsize.z / 2));

	D3DXVECTOR3 LUBold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RUBold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y + (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 LDBold = D3DXVECTOR3(g_Player.oldpos.x - (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));
	D3DXVECTOR3 RDBold = D3DXVECTOR3(g_Player.oldpos.x + (g_Player.colsize.x / 2), g_Player.oldpos.y - (g_Player.colsize.y / 2), g_Player.oldpos.z + (g_Player.colsize.z / 2));

	//頂点からold上下左右前奥のブロックを求める
	int LeftBlockOld   = (LUFold.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int RightBlockOld  = (RUFold.x + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	int UpBlockOld	   = (LUFold.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int DownBlockOld   = (LDFold.y + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	int FrontBlockOld  = (LUFold.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;
	int BehindBlockOld = (LUBold.z + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	// 0.5fずらして左右や上下でのずれがでないよう調整
	RightBlockOld  = (RUFold.x - 0.5f + (MAPCHIP_SIZE_X / 2)) / MAPCHIP_SIZE_X;
	UpBlockOld     = (LUFold.y - 0.5f + (MAPCHIP_SIZE_Y / 2)) / MAPCHIP_SIZE_Y;
	BehindBlockOld = (LUBold.z - 0.5f + (MAPCHIP_SIZE_Z / 2)) / MAPCHIP_SIZE_Z;

	//if (RightBlockOld > oldblock_x && oldblock_x == LeftBlockOld)
	//	RightBlockOld = oldblock_x;
	//if (UpBlockOld > oldblock_y && oldblock_y == DownBlockOld)
	//	UpBlockOld = oldblock_y;
	//if (BehindBlockOld > oldblock_z && oldblock_z == FrontBlockOld)
	//	BehindBlockOld = oldblock_z;


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

	// 初期化用のnextposも用意する
	D3DXVECTOR3 InitNextpos = g_Player.nextpos;

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
		ColY = 0;
	if (g_Player.move.y < 0.0f)		// プレイヤーは下に進んでいる
		ColY = 1;
	if (g_Player.move.z > 0.0f)		// プレイヤーは奥に進んでいる
		ColZ = 0;
	if (g_Player.move.z < 0.0f)		// プレイヤーは手前に進んでいる
		ColZ = 1;

	// 当たっている範囲のブロックから当たり判定のあるブロックかどうかをマップチップから調べる
	// 当たっているブロックを保存して後から計算用
	int hitcount = 0;		// 当たっているブロックの数
	D3DXVECTOR3 block_min  = D3DXVECTOR3(999, 999, 999);
	D3DXVECTOR3 block_max  = D3DXVECTOR3(-1, -1, -1);
	D3DXVECTOR3 block_last = D3DXVECTOR3(-1, -1, -1);
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

					if (CheckHitCircleBox(g_Player.nextpos, g_Player.colsize.x,
						D3DXVECTOR3(x, y, z), D3DXVECTOR3(MAPCHIP_COLSIZE_X, MAPCHIP_COLSIZE_Y, MAPCHIP_COLSIZE_Z)))
					{
						// 円の当たり判定で当たっている場合
						// 当たっているブロックの保存
						hitcount++;
						block_last.x = x;
						block_last.y = y;
						block_last.z = z;

						if (x > block_max.x) block_max.x = x;
						if (x < block_min.x) block_min.x = x;
						if (y > block_max.y) block_max.y = y;
						if (y < block_min.y) block_min.y = y;
						if (z > block_max.z) block_max.z = z;
						if (z < block_min.z) block_min.z = z;

					}

					////ChangeBlockdata(2, x, y, z);
					////D3DXVECTOR3
					//// 隣接しているブロックが 1, 当たり判定のあるブロックだと分かったので、更に細かく当たり判定を見る
					//if (CheckHit(g_Player.nextpos, g_Player.colsize,
					//	D3DXVECTOR3(x * MAPCHIP_SIZE_X, y * MAPCHIP_SIZE_Y, z * MAPCHIP_SIZE_Z), D3DXVECTOR3(MAPCHIP_COLSIZE_X, MAPCHIP_COLSIZE_Y, MAPCHIP_COLSIZE_Z)))
					//{
					//	// 当たっているブロックの保存
					//	hitcount++;
					//	block_last.x = x;
					//	block_last.y = y;
					//	block_last.z = z;

					//	if (x > block_max.x) block_max.x = x;
					//	if (x < block_min.x) block_min.x = x;
					//	if (y > block_max.y) block_max.y = y;
					//	if (y < block_min.y) block_min.y = y;
					//	if (z > block_max.z) block_max.z = z;
					//	if (z < block_min.z) block_min.z = z;


					//	// ブロックの8隅の座標
					//	D3DXVECTOR3 LUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 LDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));

					//	D3DXVECTOR3 LUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 LDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	D3DXVECTOR3 RDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					//	
					//	//////////// 円を使った当たり判定
					//	//////////// とりあえずxとzでやってみてる 半径はプレイヤーの当たり判定のサイズのとりあえずX(50.0f)を使う
					//	//////////float radius = g_Player.colsize.x / 2;
					//	//////////// まず円の原点ともう片方の点の距離を求める
					//	//////////float distance = CalculationDistance(g_Player.nextpos.x, g_Player.nextpos.z, LUF_block.x, LUF_block.z);
					//	//////////// 距離とは別にxとzの両方の差を出しておく この時、obj2 - obj1となるようにする。(obj1の内側で判定を行うため)
					//	//////////D3DXVECTOR2 difference = D3DXVECTOR2(g_Player.nextpos.x - LUF_block.x, g_Player.nextpos.z - LUF_block.z);
					//	//////////// その距離が円の半径より短いなら円の中にその点(四角形の角)が入っているので当たっている。
						//if (distance <= radius)
						//{
						//	// 当たっている処理
						//	// 半径(全体)から内側にできる三角形の斜辺(=distance)を割って割合を出す
						//	float ratio = distance / radius;	// 円の原点から角までの距離は半径に対してどのくらいの割合か。
						//	// 差に対して割合をかけてあげて、円の原点と被っている最奥の座標の差を出す
						//	D3DXVECTOR2 finpos = D3DXVECTOR2(difference.x / ratio, difference.y / ratio);

						//	// 最終的な動かす距離を出す
						//	D3DXVECTOR2 movedistance = D3DXVECTOR2(finpos.x - difference.x, finpos.y - difference.y);

						//	// 最終的に求めた座標から角の座標を引いてあげればどれだけ被っているかがわかる
						//	//D3DXVECTOR2 Cover = D3DXVECTOR2(LUF_block.x + finpos.x, LUF_block.z + finpos.y);
						//	// そしてnextposに反映させる。または最終的にそうするようにする
						//	//g_Player.nextpos.x = g_Player.nextpos.x - movedistance.x;
						//	//g_Player.nextpos.z = g_Player.nextpos.z - movedistance.y;

						//	float assx = g_Player.nextpos.x - movedistance.x;
						//	float assy = g_Player.nextpos.z - movedistance.y;

						//	SetScore(ratio * 100);
						//	//SetScore1(radius + 1000);
						//	//SetScore2(distance + 1000);
						//	SetScore1(movedistance.x + 1000);
						//	SetScore2(movedistance.y + 1000);
						//	SetScore3(finpos.x + 1000);
						//	SetScore4(finpos.y + 1000);
						//	SetScore5(assx + 1000);
						//	SetScore6(assy + 1000);

						//}
					//}
				}

			}
		}

	}

	if (hitcount > 0)
	{
		// 当たっている場合
		for (int z = block_min.z; z <= block_max.z; z++)
		{
			for (int y = block_min.y; y <= block_max.y; y++)
			{
				for (int x = block_min.x; z <= block_max.x; x++)
				{

					// ブロックの8隅の座標
					D3DXVECTOR3 LUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RUF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 LDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RDF_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z - (MAPCHIP_COLSIZE_Z / 2));

					D3DXVECTOR3 LUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RUB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y + (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 LDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X - (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));
					D3DXVECTOR3 RDB_block = D3DXVECTOR3(x * MAPCHIP_SIZE_X + (MAPCHIP_COLSIZE_X / 2), y * MAPCHIP_SIZE_Y - (MAPCHIP_COLSIZE_Y / 2), z * MAPCHIP_SIZE_Z + (MAPCHIP_COLSIZE_Z / 2));

					float radius = g_Player.colsize.x / 2;

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

						float distance = CalculationDistance(g_Player.nextpos.x, g_Player.nextpos.z, Block_pos.x, Block_pos.z);
						D3DXVECTOR2 difference = D3DXVECTOR2(g_Player.nextpos.x - Block_pos.x, g_Player.nextpos.z - Block_pos.z);

						float ratio = distance / radius;
						D3DXVECTOR2 finpos = D3DXVECTOR2(difference.x / ratio, difference.y / ratio);

						// 最終的な動かす距離を出す
						D3DXVECTOR2 movedistance = D3DXVECTOR2(finpos.x - difference.x, finpos.y - difference.y);

						float assx = g_Player.nextpos.x - movedistance.x;
						float assy = g_Player.nextpos.z - movedistance.y;

						SetScore(ratio * 100);
						//SetScore1(radius + 1000);
						//SetScore2(distance + 1000);
						SetScore1(movedistance.x + 1000);
						SetScore2(movedistance.y + 1000);
						SetScore3(finpos.x + 1000);
						SetScore4(finpos.y + 1000);
						SetScore5(assx + 1000);
						SetScore6(assy + 1000);

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


