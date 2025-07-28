//===========================================
// 
// シーンマネージャー[scene_maneger.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_maneger.h"	// シーンマネージャー
#include "../base/manager.h"		// マネージャー

namespace Scene {

	class CTitle;
	//============================================
	// コンスト
	//============================================
	CSceneManager::CSceneManager() :
		CBase(new CCommonData()),
		m_pScene(makeScene<CTitle>())
	{
		
	}
	//============================================
	// デストラクタ
	//============================================
	CSceneManager::~CSceneManager()
	{
		if (m_pScene != nullptr)
		{
			delete m_pScene;
		}
		delete m_pCommonData;
	}
	//============================================
	// 更新
	//============================================
	CBase* CSceneManager::Update()
	{
		// シーン更新
		CBase* pBaseScene = m_pScene->Update();

		if (pBaseScene != m_pScene)
		{// 返り値が変わっていたらシーン変更
			delete m_pScene;
			if (pBaseScene == nullptr)
			{
				CManager::GetInstance()->SetEnd(true);
			}
			m_pScene = pBaseScene;
		}
		return m_pScene;
	}
	//============================================
	// 描画
	//============================================
	void CSceneManager::Draw() const
	{
		if (m_pScene != nullptr)
		{
			m_pScene->Draw();
		}
	}

	//============================================
	// ポーズ中取得
	//============================================
	bool CSceneManager::GetPose()
	{
		if (m_pScene != nullptr)
		{
			return m_pScene->GetPose();
		}
		return false;
	}
}
