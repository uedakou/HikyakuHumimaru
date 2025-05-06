//===========================================
// 
// �f�o�b�N�V�[��[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// �f�o�b�N�V�[��
#include "../../../base/manager.h"		// �}�l�[�W���[
#include "../game_data.h"		// �Q�[���f�[�^
#include "../../../object/base/object_3D.h"	// �RD�I�u�W�F�N�g
#include "../../../object/base/text.h"	// �RD�I�u�W�F�N�g


namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CSceneDebug::s_bCameraFollowPlayer = true;
		const float CSceneDebug::s_fCameraRot = 2.6f;
		//============================================
		// �R���X�g���N�^
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// �V�[�������[�X

		// �v���C���[�ݒ�
			CPlayer* pPlayer = m_gameData->GetPlayer();
			pPlayer->SetNormalDraw(true);
			pPlayer->SetPoseDraw(true);
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// ���[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetTexture("data/TEXTURE/Provisional/Glass000.png");

			// �J��������
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);

			// �e�L�X�g����
			m_pText = CText::creat();

			m_fCameraRot = s_fCameraRot;

			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// �J�������v���C���[��Ǐ]���邩�ǂ���

			//CFade::creat(CFade::TYPE::WHITE_IN, 30);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			//if (m_pField != nullptr)
			//{
			//	m_pField->DeathFlag();
			//}
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CSceneDebug::Update()
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_gameData->GetPlayer();

			// �J�������v���C���[�ɒǏ]������Ȃ�
			if (m_bCameraFollowPlayer == true)
			{
				// �v���C���[���L��Ȃ�
				if (pPlayer != nullptr)
				{
#if _DEBUG
					if (pKey->GetTrigger(DIK_UP))
					{
						m_fCameraRot += 0.1f;
					}
					else if (pKey->GetTrigger(DIK_DOWN))
					{
						m_fCameraRot -= 0.1f;
					}
#endif // _DEBUG
					// �J�������v���C���[�ɒǏ]������
					D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
					pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_fCameraRot) * 300.0f, playerPos.z + cosf(m_fCameraRot) * 300.0f));	// �J�����ɓK��

					// �J�����̃v���C���[����̌���
					//char text[MAX_TXT];
					//sprintf_s(text, sizeof(text), "CameraRot:%f\n", m_fCameraRot);

					//m_pText->SetText(text);
				}
			}

			// �v���C���[�����[�v����悤�ɂ���
			// �v���C���[��null�łȂ����
			if (pPlayer != nullptr)
			{
				float posz = pPlayer->GetPosZ();
				if (posz >= 4000.0f)
				{
					pPlayer->SetPosZ(-5000.0f);
				}
			}

			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			return this;
		}
		//============================================
		// �`��
		//============================================
		void CSceneDebug::Draw() const
		{
		}

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CSceneDebug::GetPose()
		{
			return false;
		}

		template<>
		nsPrev::CBase* CBase::makeScene<CSceneDebug>(CGameData* gamaData) {
			return new CSceneDebug(this, gamaData);
		}
	}
}