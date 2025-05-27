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
#include "../../../object/obstacles_tall.h"	// ��Q��
#include "../../../object/obstacles_high.h"	// ��Q��
#include "../../../object/obstacles_low.h"	// ��Q��

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

			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			
			m_bPose = false;	// �|�[�Y��Ԑݒ�

			// �v���C���[�ݒ�
			pPlayer->SetNormalUpdate(true);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(true);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(true);		// �|�[�Y���`��ݒ�
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// ���[�V�����ݒ�
			pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
			pPlayer->SetMove(true);	// ������ݒ�
			pPlayer->SetLife(1);	// �̗͐ݒ�

			// �J��������
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);

			m_fCameraRot = s_fCameraRot;	// �J�������v���C���[��Ǐ]���邩�ǂ���

			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// �J�������v���C���[��Ǐ]���邩�ǂ���

			// ���[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetTexture("data/TEXTURE/Provisional/Glass000.png");

			// ��Q��
			CObstaclesToll::clate(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));

			CObstaclesHigh::clate(D3DXVECTOR3(0.0f, 0.0f, 2000.0f));

			CObstaclesLow::clate(D3DXVECTOR3(0.0f, 0.0f, 3000.0f));



		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			int a = 0;
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
			// �|�[�Y����
			if (pKey->GetTrigger(DIK_P))
			{
				m_bPose = !m_bPose;
				// �|�[�Y������
				if (m_bPose)
				{
					// �v���C���[�̓������~�߂�
					pPlayer->SetMove(false);
				}
				// �|�[�Y������������
				else
				{
					// �v���C���[�̓�����
					pPlayer->SetMove(true);
				}
			}
			if (m_bPose == false)
			{

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

				// �v���C���[�̗̑͂��O�ȉ��Ȃ�
				if (pPlayer->GetLife() <= 0)
				{
					return makeScene<CScen_Game_StageSelect>(m_gameData);
				}

				// �f�o�b�O�V�[���`�F���W
				if (pKey->GetTrigger(DIK_L))
				{
					return makeScene<CScen_Game_StageSelect>(m_gameData);
				}
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