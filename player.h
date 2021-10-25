/*==============================================================================

   頂点管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SIZE_X	(100.0f)
#define PLAYER_SIZE_Y	(100.0f)
#define PLAYER_SIZE_Z	(0.0f)			// 紙みたいなペラペラなのでここは0でOK,逆に数を入れると立方体になるので表示が手前にきてしまう。(player専用の表示方法にすればOK)

#define PLAYER_COL_SIZE_X	(100.0f)
#define PLAYER_COL_SIZE_Y	(100.0f)
#define PLAYER_COL_SIZE_Z	(5.0f)		// 表示的には違うけど当たり判定は作っておく。


// プレイヤー構造体
struct PLAYER
{

	D3DXVECTOR3		pos;		// 位置
	D3DXVECTOR3		oldpos;		// 前の位置
	D3DXVECTOR3		nextpos;	// 次の位置
	D3DXVECTOR3		drawpos;	// 実際の表示の位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		size;		// 大きさ
	D3DXVECTOR3		colsize;	// 当たり判定の大きさ
	D3DXVECTOR3		scl;		// 大きさの倍率

	int				texNo;		// テクスチャ
	int				act;		// どういう状態か(アニメーションとかの時使う)

	D3DXVECTOR3		move;		// 移動の力,キーを入力していなければ毎フレームごとに止まろうとする,空中とか滑りやすさで止まろうとする力は変わる

	bool			ground;		// 地面に足を付けている状態かどうか


	bool			isUse;		// true:使っている  false:未使用

	int				OldBlock_RightEnd;	// 1フレーム前の右端のブロックの値
	int				OldBlock_UpEnd;		// 1フレーム前の上端のブロックの値
	int				OldBlock_BehindEnd;	// 1フレーム前の奥端のブロックの値
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
