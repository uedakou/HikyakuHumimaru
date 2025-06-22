//============================================
//
// プリコンパイル[pch.h]
// Author:Uedakou
// 
//============================================
#ifndef _PCH_H_
#define _PCH_H_

// インクルード
#include <Windows.h>
#include "d3dx9.h"	 // 描画に必要

#include "dinput.h"
#include "Xinput.h"

// ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		// 描画に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9,lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// DirectXコンポーネント使用に必要
#pragma comment(lib,"winmm.lib")	// システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	// Dインプット
#pragma comment(lib,"Xinput.lib")	// Xインプット
//#pragma comment(lib,"x86")		// 
//#pragma comment(lib,"Redist")	// Xインプット

// C++ テキスト
#include <iostream>	// インアウトストリーム
#include <string>
using namespace std;
//#include "../object/base/text.h"	// テキスト

// マクロ定義
#define SCREEN_W (1280)			// ウィンドウの幅
#define SCREEN_H (720)			// ウィンドウの高さ

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define FPS (60)	// FPS

#define ANIM_SLEEP (5)	// アニメーション速度調整

#define CLASS_NAME "CatasrtopheMobile"		// ウィンドウクラス名前
#define WINDOW_NAME "CatasrtopheMobile"		// ウィンドウの名前

// 頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変更用係数（1.0fで固定）
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;
// 頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_3D;

#endif // !_PCH_H_