#pragma once

#include "main.h"
#include "renderer.h"

#define MAP_X_MAX		(20)
#define MAP_Y_MAX		(10)
#define MAP_Z_MAX		(4)


#define ROT_90		(1.57f)			// rot‚É“ü‚ê‚é‚Æ–ñ90“x‚Ì‰ñ“],3.14=180do,6.28=360do

#define MAPCHIP_SIZE_X		(128.0f)
#define MAPCHIP_SIZE_Y		(128.0f)
#define MAPCHIP_SIZE_Z		(128.0f)

#define TEST01 (50)


HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

int GetMapEnter(D3DXVECTOR2 pos);
void SetCurrentMap(int next);

int CheckBlockdata(int BlockX, int BlockY, int BlockZ);