//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(5)			// 桁数




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);

void SetScore(int score);

void SetScore1(int score);
void SetScore2(int score);
void SetScore3(int score);
void SetScore4(int score);
void SetScore5(int score);
void SetScore6(int score);
