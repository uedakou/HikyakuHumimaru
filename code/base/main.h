//===========================================
// 
// メイン[main.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MAIN_H_	// このマクロ定義されてないなら
#define _MAIN_H_	// 二重インクルード防止のマクロ
#include "pch.h"	// プリコンパイル済みヘッダ


class CApplication
{
public:
	CApplication();
	~CApplication();

	bool Init(HINSTANCE hInstance, int nCmdShow); // 初期化処理
	void Uninit();	// 解放処理
	void Run();		// メインループ
	void OnKeyDown(WPARAM key);	// キーボード入力に対する処理

private:
	HWND m_hWnd;				// アプリケーションのウィンドウハンドル
	WNDCLASSEX m_wcex;			// ウィンドウクラス情報構造体
	MSG m_msg;					// メッセージ構造体
	DWORD m_dwExecLastTime;		// 最後に処理を行った時間（ms）
	DWORD m_dwFPSLostTime;		// 最後にFPSを計測した時間（ms）
	DWORD m_dwFrameCount;		// フレーム数カウント（FPS計測用）
};
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
int GetFPS();	// FPS取得

#endif // _MAIN_H_