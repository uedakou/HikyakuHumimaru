//===========================================
// 
// �Q�[���}�l�[�W���[[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// �Q�[���}�l�[�W���[	
#include "game_data.h"			// �Q�[���f�[�^
#define g_bDebug 1
namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;						// �Q�[���S�̏���
		class CSceneDebug;				// �f�o�b�O
		class CStage_Tutorial;			// �`���[�g���A��
		class CScen_Game_StageSelect;	// �X�e�[�W�I��
		//============================================
		// �R���X�g���N�^
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData())

		{

			m_pScene = makeScene<Play>(m_gameData);
#if g_bDebug
			m_pStageController = makeScene<CScen_Game_StageSelect>(m_gameData);
#else 
			m_pStageController = makeScene<CSceneDebug>(m_gameData);
#endif // 0
		}
		//============================================
		// �f�X�g���N�^
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
		}

		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			if (m_pScene != nullptr)
			{
				auto p = m_pScene->Update();
				if (p != m_pScene)
				{
					delete m_pScene;
					auto p2 = dynamic_cast<CBase*>(p);
					if (p2 != nullptr)
					{
						m_pScene = p2;
						return this;
					}
					else
					{
						m_pScene = nullptr;
						return p;
					}
				}
			}
			if (m_pStageController != nullptr)
			{
				auto p = m_pStageController->Update();
				if (p != m_pStageController)
				{
					delete m_pStageController;

					if (true)
					{

					}
					m_pStageController = p;
					return this;
				}
			}
			return this;
		}
		//============================================
		// �`��
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
		// �R���X�g���N�^
		//============================================

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CGameManager::GetPose()
		{
			if (m_pScene != nullptr)
			{
				return m_pScene->GetPose();
			}
			return false;
		}
	}
	template<>
	Scene::CBase* nsThis::nsPrev::CBase::makeScene<nsThis::CGameManager>() {
		return new nsThis::CGameManager(this);
	}
}