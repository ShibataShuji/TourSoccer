#pragma once

#include "main.h"
#include "renderer.h"

#define MAP_X_MAX		(20)
#define MAP_Y_MAX		(10)
#define MAP_Z_MAX		(4)


#define ROT_90		(1.57f)			// rotに入れると約90度の回転,3.14=180do,6.28=360do

#define MAPCHIP_SIZE_X		(128.0f)
#define MAPCHIP_SIZE_Y		(128.0f)
#define MAPCHIP_SIZE_Z		(128.0f)

#define MAPCHIP_COLSIZE_X		(128.0f)		// posからブロックを求めるとき128.0fとかで左右の片方からだけ
#define MAPCHIP_COLSIZE_Y		(128.0f)		// intで小数点切った時のずれを防ぐため。
#define MAPCHIP_COLSIZE_Z		(128.0f)

#define TEST01 (50)


HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY, int BlockZ);
void ChangeBlockdata(int changenum, int BlockX, int BlockY, int BlockZ);

bool CheckHit(D3DXVECTOR3 obj1_pos, D3DXVECTOR3 obj1_colsize, D3DXVECTOR3 obj2_pos, D3DXVECTOR3 obj2_colsize);