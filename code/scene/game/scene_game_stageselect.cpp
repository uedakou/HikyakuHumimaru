//===========================================
// 
// �Q�[���X�e�[�W�I��[scene_game_stageselect.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_stageselect.h"			// �X�e�[�W�Z���N�g
#include "../../object/base/object.h"		// �I�u�W�F�N�g
#include "../../object/base/object_3D.h"	// �I�u�W�F�N�g3d
#include "../../object/base/object_2D.h"	// �I�u�W�F�N�g2d
#include "../../base/input.h"				// ����
#include "../../object/player.h"			// �v���C���[
#include "game_data.h"						//�@�Q�[���f�[�^

namespace Scene {
	namespace Game {
		// ���N���X
		class CSceneDebug;				// �f�o�b�O
		class CStage_000;				// �X�e�[�W000
		class CStage_001;				// �X�e�[�W001

		// �萔��`
		const int CScen_Game_StageSelect::s_nPressHoldLimit = 10;	// ���͊J�n�J�E���g
		const D3DXVECTOR3 CScen_Game_StageSelect::s_SelectSiz = { 200.0f, 200.0f, 0.0f };	// ���͊J�n�J�E���g
		const D3DXVECTOR3 CScen_Game_StageSelect::s_NotSelectSiz = { 100.0f, 100.0f, 0.0f };	// ���͊J�n�J�E���g

		CScen_Game_StageSelect::CScen_Game_StageSelect(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// �V�[�������[�X
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();

			m_bPose = false;	// �|�[�Y���
			m_nSetlect = 0;	// ���I��
			m_nCntPressHold = 0;	// �������J�E���g
			m_bNext = false;	// ���I���ς݂��ǂ���
			// �X�e�[�W�I���̃I�u�W�F�N�g
			for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++ )
			{
				m_pStage[nCnt] = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f + 200.0f * nCnt, SCREEN_H * 0.5f, 0.0f), s_NotSelectSiz);
				switch (static_cast<Select>(nCnt))
				{
				case Select::STAGE_000:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_000.png");
					break;
				case Select::STAGE_001:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_001.png");
					break;
				case Select::STAGE_002:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_002.png");
					break;
				default:
					break;
				}
			}
			// ��ڂ̃T�C�Y��I���ς݂ɂ���
			m_pStage[0]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));


			// �w�i
			CObject2D* pBG = nullptr;
			pBG = CObject2D::creat(2, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0));	// ����
			pBG->SetTexture("data/TEXTURE/Provisional/BG_000.png");	// �e�N�X�`��

			pCamera->SetPosV(D3DXVECTOR3(0.0f, 100.0f, -400.0f));
			pCamera->SetRotX(1.3f);	// �J��������

			// �v���C���[�ݒ�
			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾
			pPlayer->SetNormalUpdate(false);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetPoseUpdate(false);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(false);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(false);		// �|�[�Y���`��ݒ�
			pPlayer->SetMove(false);	// ���[�V�����̓�����ݒ�
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�
		}

		CScen_Game_StageSelect::~CScen_Game_StageSelect()
		{
		}

		nsPrev::CBase* CScen_Game_StageSelect::Update()
		{

			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[
			CInputKeyboard* pInKey = pManager->GetInKey();	// �L�[�{�[�h����

			if (pInKey->GetTrigger(DIK_P))
			{
				m_bPose = !m_bPose;
			}

			if (m_bPose == false)
			{


				int nSetlectOld = m_nSetlect;	// ���ʒu���L��
				// �����͂�����
				if (pInKey->GetTrigger(DIK_A) ||
					pInKey->GetTrigger(DIK_LEFT))
				{
					// �I�������肳��Ă��Ȃ�������
					if (m_bNext == false)
					{
						// �I������߂�
						m_nSetlect--;
						// �ŏ��ȉ��Ȃ�߂�Ȃ��悤�ɂ���
						if (m_nSetlect < 0)
						{
							m_nSetlect = 0;
						}
					}

				}
				// �����͂���������
				//else if (pInKey->GetRepeat(DIK_A) ||
				//	pInKey->GetRepeat(DIK_LEFT))
				//{
				//	// �A�����͂��J�E���g����
				//	m_nCntPressHold++;
				//	// c_nPressHoldLimit�ȏ㒷����������
				//	if (m_nCntPressHold >= c_nPressHoldLimit)
				//	{
				//		// �I�������肳��Ă��Ȃ�������
				//		if (m_bNext == false)
				//		{
				//			// �I������߂�
				//			m_nSetlect--;
				//			// �ŏ��ȉ��Ȃ�߂�Ȃ��悤�ɂ���
				//			if (m_nSetlect < 0)
				//			{
				//				m_nSetlect = 0;
				//			}
				//		}
				//	}

				//}
				// �E���͂�����
				else if (pInKey->GetTrigger(DIK_D) ||
					pInKey->GetTrigger(DIK_RIGHT))
				{
					// �I�������肳��Ă��Ȃ�������
					if (m_bNext == false)
					{
						// �I������i�߂�
						m_nSetlect++;
						// �ő�ȏ�Ȃ��ɐi�܂Ȃ��悤�ɂ���
						if (m_nSetlect >= static_cast<int>(Select::MAX))
						{
							m_nSetlect = static_cast<int>(Select::MAX) - 1;
						}
					}
				}
				// �E���͂���������
				//else if (pInKey->GetRepeat(DIK_A) ||
				//	pInKey->GetRepeat(DIK_LEFT))
				//{
				//	// �A�����͂��J�E���g����
				//	m_nCntPressHold++;
				//	// c_nPressHoldLimit�ȏ㒷����������
				//	if (m_nCntPressHold >= c_nPressHoldLimit)
				//	{
				//		// �I�������肳��Ă��Ȃ�������
				//		if (m_bNext == false)
				//		{
				//			// �I������i�߂�
				//			m_nSetlect++;
				//			// �ő�ȏ�Ȃ��ɐi�܂Ȃ��悤�ɂ���
				//			if (m_nSetlect >= static_cast<int>(Select::MAX))
				//			{
				//				m_nSetlect = static_cast<int>(Select::MAX) - 1;
				//			}
				//		}
				//	}
				//}
				// �ړ�����͂���Ă��Ȃ�������
				else
				{
					m_nCntPressHold = 0;
				}

				// �������͂�����
				if (pInKey->GetTrigger(DIK_RETURN) ||
					pInKey->GetTrigger(DIK_SPACE))
				{
					m_bNext = true;
				}

				//���I���ƌ��I�����������
				if (m_nSetlect != nSetlectOld)
				{
					// �I����������傫������
					m_pStage[m_nSetlect]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
					// �I�����Ă�����������������
					m_pStage[nSetlectOld]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 0.0f
					));
					// ���ɑI��������
					if (m_nSetlect < nSetlectOld)
					{
						// ���Ɉړ�������
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(200.0f);
						}
					}
					// �E�ɑI��������
					else
					{
						// �E�Ɉړ�������
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(-200.0f);
						}
					}

				}

				if (m_bNext == true)
				{// �I�������肵����
					switch (static_cast<Select>(m_nSetlect))
					{
					case Select::STAGE_000:

						return makeScene<CStage_000>(m_gameData);
						break;
					case Select::STAGE_001:
						return makeScene<CStage_001>(m_gameData);
						break;
					case Select::STAGE_002:
						return makeScene<CSceneDebug>(m_gameData);
						break;
					default:
						break;
					}
				}
			}
			return this;
		}

		void CScen_Game_StageSelect::Draw() const
		{
		}

		bool CScen_Game_StageSelect::GetPose()
		{
			return m_bPose;
		}
		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CScen_Game_StageSelect>(CGameData* gamaData) {
			return new CScen_Game_StageSelect(this, gamaData);
		}
	}
}