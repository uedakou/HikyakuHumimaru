//===========================================
// 
// ゲームマネージャー[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// ゲームマネージャー	
#include "game_data.h"			// ゲームデータ

#define g_bDebug 1
namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;						// ゲーム全体処理
		class CSceneDebug;				// デバッグ
		class CStage_Tutorial;			// チュートリアル
		class CScen_Game_StageSelect;	// ステージ選択
		//============================================
		// コンストラクタ
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData())

		{

			m_pScene = makeScene<Play>();
#if g_bDebug
			m_pStageController = makeScene<CScen_Game_StageSelect>();
#else 
			m_pStageController = makeScene<CSceneDebug>(m_gameData);
#endif // 0
		}
		//============================================
		// デストラクタ
		//============================================
		CGameManager::~CGameManager()
		{
			if (m_pScene != nullptr)
			{
				delete m_pScene;
			}
			if (m_pStageController != nullptr)
			{
				delete m_pStageController;
			}
			if (m_gameData != nullptr)
			{
				delete m_gameData;
			}
		}

		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			if (m_pScene != nullptr)
			{
				auto pBaseScene = m_pScene->Update();
			}
			if (m_pStageController != nullptr)
			{
				auto pBaseScene = m_pStageController->Update();
				if (pBaseScene != m_pStageController)
				{
					delete m_pStageController;

					auto pBaseScene2 = dynamic_cast<CBase*>(pBaseScene);
					if (pBaseScene2 != nullptr)
					{
						m_pStageController = pBaseScene2;
						return this;
					}
					else
					{
						m_pStageController = nullptr;
						return pBaseScene;
					}
				}
			}
			return this;
		}
		//============================================
		// 描画
		//============================================
		void CGameManager::Draw() const
		{
			if (m_pScene != nullptr)
			{
				m_pScene->Draw();
			}
			if (m_pStageController != nullptr)
			{
				m_pStageController->Draw();
			}
		}
		//============================================
		// コンストラクタ
		//============================================

		//============================================
		// ポーズ中取得
		//============================================
		bool CGameManager::GetPose()
		{
			if (m_pScene != nullptr)
			{
				return m_pScene->GetPose();
			}
			return false;
		}
		/// <summary>
		/// 次シーンが設定されていたら変える
		/// </summary>
		nsPrev::CBase* CGameManager::JoinNextScene()
		{
			// 次シーンが有るなら
			if (m_pNextScene)
			{
				delete m_pScene;	// 現在シーンを破棄
				auto p2 = dynamic_cast<CBase*>(m_pNextScene);
				if (p2 != nullptr)
				{
					m_pScene = p2;
					return this;
				}
				else
				{
					m_pScene = nullptr;
					return m_pNextScene;
				}
			}
			return this;
		}
	}
	template<>
	Scene::CBase* nsThis::nsPrev::CBase::makeScene<nsThis::CGameManager>() {
		return new nsThis::CGameManager(this);
	}
}