//=============================================================================
//
// ポリゴン表示処理 [polygon.cpp]
// Author : 
//
//=============================================================================
#include <string.h>
#include "main.h"
#include "input.h"
#include "camera.h"
#include "polygon.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX		(1)							// テクスチャの数

#define	VALUE_MOVE		(5.0f)						// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

#define	SIZE_X			(200.0f)					// 地面のサイズ(X方向)
#define SIZE_Y          (100.0f)					// 地面のサイズ(Y方向)
#define	SIZE_Z			(100.0f)					// 地面のサイズ(Z方向)

#define VERTEX_NUM       (1200)

#define OBJECT_NUM       (199)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPolygon(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// 頂点情報

static OBJECT g_Object[OBJECT_NUM];


static OBJECTDATA g_ObjectData[OBJECT_NUM];

int creatcooltime;


// 頂点配列
static VERTEX_3D g_VertexArray[VERTEX_NUM] = {
	//天井1
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	//底6
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	//右側面2
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y,  SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	//左側面5
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y,-SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	//奥側面3
	{D3DXVECTOR3( SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X,-SIZE_Y, SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.66f, 0.5f)},
	//手前側面4
	{D3DXVECTOR3(-SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.5f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3( SIZE_X, SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 0.5f)},
	{D3DXVECTOR3 (SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.33f, 1.0f)},
	{D3DXVECTOR3(-SIZE_X,-SIZE_Y, -SIZE_Z), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f)},


};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	creatcooltime = 0;


	// 頂点バッファの作成
	MakeVertexPolygon();


	// オブジェクトデータ構造体の初期化
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		// テクスチャ生成
		g_ObjectData[i].g_Tex = LoadTexture("data/TEXTURE/saikoro_2x3.png");

		// 位置・回転・スケールの初期設定
		g_ObjectData[i].pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 配置する座標
		g_ObjectData[i].rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 配置の角度
		g_ObjectData[i].size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	// 配置の角度
		g_ObjectData[i].scl  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 大きさの倍率

		g_ObjectData[i].act = 0;
		g_ObjectData[i].arraynum = 0;
		g_ObjectData[i].DisappearanceCount = -1;
		g_ObjectData[i].isUse = false;

		// g_ObjectData[i].mtxWorld;	// ワールドマトリックス(よくわかってない)
	}

	int texnoo = LoadTexture("data/TEXTURE/field000.jpg");

	SetObject(0, texnoo, D3DXVECTOR3(200.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		0.0f, 0.0f, 1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{

	// 全てのオブジェクトデータを使われていない状態にする
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if(g_ObjectData[i].isUse == true)
			g_ObjectData[i].isUse = false;
	}

	// 頂点バッファの解放
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void ReleasePolygon(void)
{
	// 頂点バッファの解放
	if (g_VertexBuffer) {
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	PLAYER player = *GetPlayer();

	if (creatcooltime >= 0)
		creatcooltime--;

	CAMERA *cam = GetCamera();

	for (int i = 0; i < OBJECT_NUM; i++)
	{

		//// 回転させちゃう
		//if (GetKeyboardPress(DIK_LEFT))
		//{
		//	// g_ObjectData[i].rot.y -= VALUE_ROTATE;
		//	if (creatcooltime < 0)
		//	{
		//		creatcooltime = 60;
		//		SceneFadeIn(SCENE_TITLE);

		//		int texnoo = LoadTexture("data/TEXTURE/saikoro_2x3.png");
		//		SetObject(texnoo, D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//			D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		//			0.0f, 0.0f, 1.0f, 1.0f,
		//			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//			false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);
		//	}
		//}
		//if (GetKeyboardPress(DIK_RIGHT))
		//{
		//	//g_ObjectData[i].rot.y += VALUE_ROTATE;

		//	if (creatcooltime < 0)
		//	{
		//		creatcooltime = 60;
		//		int texnoo = LoadTexture("data/TEXTURE/field000.jpg");
		//		SetObject(texnoo, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		//			D3DXVECTOR3(100.0f, 100.0f, 100.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),
		//			0.0f, 0.0f, 1.0f, 1.0f,
		//			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//			false, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -1);
		//	}


		//}
		//if (GetKeyboardPress(DIK_UP))
		//{
		//	g_ObjectData[i].rot.x -= VALUE_ROTATE;
		//}
		//if (GetKeyboardPress(DIK_DOWN))
		//{
		//	g_ObjectData[i].rot.x += VALUE_ROTATE;
		//}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_ObjectData[i].rot.y = g_ObjectData[i].rot.x = 0.0f;
		//}



		// 無理やりポリゴンの頂点情報を初期化してもう一度更新させてるつもり
		ReleasePolygon();
		// 頂点バッファの作成
		MakeVertexPolygon();

#ifdef _DEBUG	// デバッグ情報を表示する
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], " rotX:%.2f rotY:%.2f", g_ObjectData[i].rot.x, g_ObjectData[i].rot.y);
		//sprintf(&str[strlen(str)], " posX:%.2f posY:%.2f", player.pos.x, player.pos.y);

#endif

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// 使用しているのデータを探す
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if (g_ObjectData[i].isUse == true)		// 使用しているデータを見つける
		{

			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ObjectData[i].g_Tex));


			D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ObjectData[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_ObjectData[i].scl.x, g_ObjectData[i].scl.y, g_ObjectData[i].scl.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectData[i].rot.y, g_ObjectData[i].rot.x, g_ObjectData[i].rot.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_ObjectData[i].pos.x, g_ObjectData[i].pos.y, g_ObjectData[i].pos.z);
			D3DXMatrixMultiply(&g_ObjectData[i].mtxWorld, &g_ObjectData[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_ObjectData[i].mtxWorld);

			int startlocation = 6 * i + 0;

			// ポリゴン描画(描画に使う頂点の数を指定)
			GetDeviceContext()->Draw(6, startlocation);


			// 消滅カウントを進める処理。-1ずつしていき0になったら消滅。元々-1指定など負の数の場合無視
			if (g_ObjectData[i].DisappearanceCount > 0)
				g_ObjectData[i].DisappearanceCount--;

			// 消滅カウントが0になったら消滅させる
			if (g_ObjectData[i].DisappearanceCount == 0)
				g_ObjectData[i].isUse = false;
		}
	}


}

HRESULT MakeVertexPolygon(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;;
	bd.ByteWidth = sizeof(VERTEX_3D) * VERTEX_NUM;	// 頂点の数分メモリ(頂点バッファ)を確保
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// グローバルの頂点配列から頂点バッファをつくる
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = g_VertexArray;

	GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	return S_OK;
}

void DrawPolygonObjectCenter(int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Size,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, D3DXVECTOR3 Rot,
	bool UseNormal, D3DXVECTOR3 Normal)
{

	//////// 法線(光の当たり方を使わないならば)
	//////if (!UseNormal)
	//////{
	//////	// 本当はライトを無視してずっと明るくしたいけど今のところわからないから
	//////	// とりあえず今のライトで明るい設定。
	//////	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//////}

	//////// ワールドマテリックスの定義(よくわかってないなにこれ)
	//////D3DXMATRIX mtxWorld;

	//////// スケールの定義と初期化(厚さ？)
	//////D3DXVECTOR3 scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//////float LU = Pos.x - (Size.x / 2);
	//////float RU = Pos.x + (Size.x / 2);
	//////float LD = Pos.x + (Size.x / 2);

	//////// 引数からオブジェクトの端っこの座標を求める
	//////// Left Rigt Up Down in Flont Behind
	//////D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));
	//////D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));

	//////D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));
	//////D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));


	//////// 頂点配列
	//////VERTEX_3D g_VertexArray_List[LIST_VERTEX_NUM] = {

	//////{D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V)},
	//////{D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V)},
	//////{D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH)},
	//////{D3DXVECTOR3(RUF.x, RUF.y, RUF.y), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V)},
	//////{D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH)},
	//////{D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH)},

	//////};


	//////// 頂点バッファ生成
	//////D3D11_BUFFER_DESC bd;
	//////ZeroMemory(&bd, sizeof(bd));
	//////bd.Usage = D3D11_USAGE_DYNAMIC;;
	//////bd.ByteWidth = sizeof(VERTEX_3D) * LIST_VERTEX_NUM;	// 頂点の数分メモリ(頂点バッファ)を確保
	//////bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//////bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//////// グローバルの頂点配列から頂点バッファをつくる
	//////D3D11_SUBRESOURCE_DATA sd;
	//////ZeroMemory(&sd, sizeof(sd));
	//////sd.pSysMem = g_VertexArray_List;

	//////GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);



	//////// 頂点バッファ設定
	//////UINT stride = sizeof(VERTEX_3D);
	//////UINT offset = 0;
	//////GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	//////// プリミティブトポロジ設定
	//////GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//////// マテリアル設定
	//////MATERIAL material;
	//////ZeroMemory(&material, sizeof(material));
	//////material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//////SetMaterial(material);

	//////// テクスチャ設定
	//////GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));


	//////D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//////// ワールドマトリックスの初期化
	//////D3DXMatrixIdentity(&mtxWorld);

	//////// スケールを反映
	//////D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//////// 回転を反映
	//////D3DXMatrixRotationYawPitchRoll(&mtxRot, Rot.y, Rot.x, Rot.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//////// 移動を反映
	//////D3DXMatrixTranslation(&mtxTranslate, Pos.x, Pos.y, Pos.z);
	//////D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//////// ワールドマトリックスの設定
	//////SetWorldMatrix(&mtxWorld);

	//////// ポリゴン描画(描画に使う頂点の数を指定)
	//////GetDeviceContext()->Draw(LIST_VERTEX_NUM, 0);

}

void DrawPolygonObjectLeftTop()
{

}

// surfaceはサイコロのどの面を描きますか。0:正面,1:後ろ側,2:上側,3:下側,4:右側,5:左側
void SetObject(int surface, int texNo, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Size, D3DXVECTOR3 Scl,
	float U, float V, float UW, float VH,
	D3DXCOLOR Color, 
	bool UseNormal, D3DXVECTOR3 Normal, int disappearance_count)
{

	// 未使用のデータを探す
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		if (g_ObjectData[i].isUse == false)		// 未使用状態のデータを見つける
		{


			//// 法線(光の当たり方を使わないならば)
			//if (!UseNormal)
			//{
			//	// 本当はライトを無視してずっと明るくしたいけど今のところわからないから
			//	// とりあえず今のライトで明るい設定。
			//	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//}

			// テクスチャ生成
			g_ObjectData[i].g_Tex = texNo;

			// 位置・回転・スケールの初期設定
			g_ObjectData[i].pos  = Pos;		// 配置する座標
			g_ObjectData[i].rot  = Rot;		// 配置の角度
			g_ObjectData[i].scl  = Scl;		// 大きさの倍率
			g_ObjectData[i].size = Size;	// 大きさ,直径

			g_ObjectData[i].act = 0;
			g_ObjectData[i].arraynum = 6 * i;
			g_ObjectData[i].DisappearanceCount = disappearance_count;
			g_ObjectData[i].isUse = true;		// 使用するのでtrueにする


			// 引数の座標などからオブジェクトのポリゴンの8この隅っこの座標を求める
			// Left Rigt Up Down in Flont Behind
			// 上手くいかなかった計算方法↓
			/*D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));
			D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z - (Size.z / 2));

			D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y + (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));
			D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + (Size.x / 2), Pos.y - (Size.y / 2), Pos.z + (Size.z / 2));*/

			// 上手く言った計算方法↓
			D3DXVECTOR3 LUF = D3DXVECTOR3(Pos.x - Size.x, Pos.y + Size.y, Pos.z - Size.z);
			D3DXVECTOR3 RUF = D3DXVECTOR3(Pos.x + Size.x, Pos.y + Size.y, Pos.z - Size.z);
			D3DXVECTOR3 LDF = D3DXVECTOR3(Pos.x - Size.x, Pos.y - Size.y, Pos.z - Size.z);
			D3DXVECTOR3 RDF = D3DXVECTOR3(Pos.x + Size.x, Pos.y - Size.y, Pos.z - Size.z);

			D3DXVECTOR3 LUB = D3DXVECTOR3(Pos.x - Size.x, Pos.y + Size.y, Pos.z + Size.z);
			D3DXVECTOR3 RUB = D3DXVECTOR3(Pos.x + Size.x, Pos.y + Size.y, Pos.z + Size.z);
			D3DXVECTOR3 LDB = D3DXVECTOR3(Pos.x - Size.x, Pos.y - Size.y, Pos.z + Size.z);
			D3DXVECTOR3 RDB = D3DXVECTOR3(Pos.x + Size.x, Pos.y - Size.y, Pos.z + Size.z);


			// 頂点配列の設定
			switch (surface) {
			case 0:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;

			case 1:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 2:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 3:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 4:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(RUF.x, RUF.y, RUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(RUB.x, RUB.y, RUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDB.x, RDB.y, RDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;
			case 5:
				g_VertexArray[6 * i + 0] = { D3DXVECTOR3(LUB.x, LUB.y, LUB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V) };
				g_VertexArray[6 * i + 1] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 2] = { D3DXVECTOR3(LDB.x, LDB.y, LDB.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				g_VertexArray[6 * i + 3] = { D3DXVECTOR3(LUF.x, LUF.y, LUF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V) };
				g_VertexArray[6 * i + 4] = { D3DXVECTOR3(RDF.x, RDF.y, RDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U + UW, V + VH) };
				g_VertexArray[6 * i + 5] = { D3DXVECTOR3(LDF.x, LDF.y, LDF.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(U, V + VH) };
				break;


			}


			return;					// セットできたので終了する
		}
	}

	// 未使用状態のデータが見つからなかったらここにくるのでエラーとして強制終了
	exit(1);

}