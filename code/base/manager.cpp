//===========================================
// 
// 全体マネージャー[managerer.cpp]
// Auther:UedaKou
// 
//===========================================
#include "manager.h"	// マネージャー
#include "../object/base/object.h"
#include "../object/base/text.h"	// テキスト


bool CManager::m_bEnd = false;
//============================================
// コンストラクタ
//============================================
CManager::CManager()
{
	m_pRenderer = nullptr;			// レンダラー
	m_pLight = nullptr;				// ライト
	m_pCamera = nullptr;			// カメラ
	m_pFog = nullptr;				// フォグ
	m_pSound = nullptr;				// サウンド

	m_pInkey = nullptr;				// キーボード
	m_pInMouse = nullptr;			// マウス
	m_pJoiKey = nullptr;			// ジョイパッド

	m_pSceneManager = nullptr;		// シーンマネージャー

	m_pDebugText = nullptr;			// デバッグ用テキスト
}
//============================================
// デストラクタ
//============================================
CManager::~CManager()
{
}
//============================================
// 初期化
//============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND nWnd, BOOL bWindow)
{
	// レンダラー
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(nWnd, bWindow);
	}
	// ライト
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}
	// カメラ
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}
	// フォグ
	if (m_pFog == nullptr)
	{
		m_pFog = CFog::create();
	}
	// サウンド
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;
		m_pSound->InitSound(nWnd);
	}



	// 入力
	if (m_pInkey == nullptr)
	{// キーボード
		m_pInkey = new CInputKeyboard;
		m_pInkey->Init(hInstance, nWnd);
	}
	if (m_pInMouse == nullptr)
	{// マウス
		m_pInMouse = new CInputMouse;
		m_pInMouse->Init(hInstance, nWnd);
	}
	// ジョイパッド入力
	if (m_pJoiKey == nullptr)
	{
		m_pJoiKey = new CInputJoypad;
		m_pJoiKey->Init();
	}
	// シーンマネージャー
	if (m_pSceneManager == nullptr)
	{
		m_pSceneManager = new Scene::CSceneManager;
	}
	// デバッグテキスト
	if (m_pDebugText == nullptr)
	{
		m_pDebugText = CText::create();
	}

	return S_OK;
}
//============================================
// 終了
//============================================
void CManager::Uninit()
{
	// デバッグテキスト
	if (m_pDebugText != nullptr)
	{
		m_pDebugText->Release();
		m_pLight = nullptr;
	}
	// ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	// カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	// キーボード入力
	if (m_pInkey != nullptr)
	{
		m_pInkey->Uninit();
		delete m_pInkey;
		m_pInkey = nullptr;
	}
	// ジョイパッド入力
	if (m_pJoiKey != nullptr)
	{
		m_pJoiKey->Uninit();
		delete m_pJoiKey;
		m_pJoiKey = nullptr;
	}
	// シーンマネージャー
	if (m_pSceneManager != nullptr)
	{
		delete m_pSceneManager;
		m_pSceneManager = nullptr;
	}
	// レンダラー
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}
//============================================
// 更新
//============================================
void CManager::Update()
{
	// デバッグテキスト
	if (m_pDebugText != nullptr)
	{
		m_pDebugText->ClearText();
	}
	// レンダラー
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	// ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}
	// カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	// キーボード入力
	if (m_pInkey != nullptr)
	{
		m_pInkey->Update();
	}
	// マウス入力
	if (m_pInMouse != nullptr)
	{
		m_pInMouse->Update();
	}
	// ジョイパッド入力
	if (m_pJoiKey != nullptr)
	{
		m_pJoiKey->Update();
	}
	// シーンマネージャー
	if (m_pSceneManager != nullptr)
	{
		m_pSceneManager->Update();
	}

	CObject::ReleaseDeathFlag();
}
//============================================
// 描画
//============================================
void CManager::Draw()
{
	// レンダラー
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();	
	}
}