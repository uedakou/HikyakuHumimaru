//===========================================
// 
// �X�e�[�W000[stage_tutorial.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_000.h"		// �`���[�g���A��

#include "../../../object/player.h"	// �v���C���[
#include "../../../object/base/object_2D.h"	// �|�b�v�A�b�v�p2D
#include "../../../object/base/object_3D.h"	// �|�b�v�A�b�v�p3D
#include "../../../object/base/object_X.h"	// �|�b�v�A�b�v�pX
#include "../../../object/base/object_fade.h"	// �t�F�[�h
#include "../../../object/base/object_billboard.h"	// �r���{�[�h
#include "../game_data.h"	// �Q�[���f�[�^
#include "../../../object/base/text.h"	// �e�L�X�g

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CStage_000::s_bCameraFollowPlayer = true;	// �J�������v���C���[��Ǐ]���邩�ǂ���
		const float CStage_000::s_fCameraRot = 2.6f;	// �v���C���[����̃J�����̊p�x
		const float CStage_000::s_fGool = 20000.0f;	// �S�[������

		// �`���[�g���A��
		const float CStage_000::s_fTutorial_000 = 2000.0f;	// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_001 = 4000.0f;		// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_002 = 6000.0f;		// �`���[�g���A���C�x���g
		const float CStage_000::s_fTutorial_003 = 6000.0f;		// �`���[�g���A���C�x���g
		const bool CStage_000::s_bTutorial_000 = false;	// �`���[�g���A���C�x���g
		const bool CStage_000::s_bTutorial_001 = false;		// �`���[�g���A���C�x���g
		const bool CStage_000::s_bTutorial_002 = false;		// �`���[�g���A���C�x���g
		const bool CStage_000::s_bTutorial_003 = false;		// �`���[�g���A���C�x���g
		const D3DXVECTOR3 CStage_000::s_TutorialPopupPos = { 1000.0f, 300.0f, 0.0f };	// �`���[�g���A���̃|�b�v�A�b�v�̈ʒu
		const D3DXVECTOR3 CStage_000::s_TutorialPopupSiz = { 300.0f, 200.0f, 0.0f };	// �`���[�g���A���̃|�b�v�A�b�v�̑傫��
		//============================================
		// �R���X�g
		//============================================
		CStage_000::CStage_000(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// �V�[�������[�X

			// �����o�ϐ��ݒ�
			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// �J�������v���C���[��Ǐ]���邩�ǂ���
			m_fCameraRot = s_fCameraRot;	// �v���C���[����̃J�����̊p�x
			m_fTutorialRange = 0.0f;	// �`���[�g���A���C�x���g�����͈̔͏�����

			m_bTutorial_000 = s_bTutorial_000;	// �`���[�g���A���C�x���g�t���O
			m_bTutorial_001 = s_bTutorial_001;	// �`���[�g���A���C�x���g�t���O
			m_bTutorial_002 = s_bTutorial_002;	// �`���[�g���A���C�x���g�t���O
			m_bTutorial_003 = s_bTutorial_003;	// �`���[�g���A���C�x���g�t���O

			for (int nCnt = 0; nCnt < static_cast<int>(TUTORIAL::MAX); nCnt++)
			{
				m_pTutorealPopup[nCnt] = CObject2D::creat(D3DXVECTOR3(s_TutorialPopupPos), D3DXVECTOR3(s_TutorialPopupSiz));// ����
				m_pTutorealPopup[nCnt]->SetPoseDraw(false);
				m_pTutorealPopup[nCnt]->SetNormalDraw(false);
				switch (static_cast<TUTORIAL>(nCnt))
				{
				case TUTORIAL::Tutorial_000:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_001:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_002:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_003:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				default:
					Beep(1000, 300);
					break;
				}
			}

			// �v���C���[�ݒ�
			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾
			pPlayer->SetNormalUpdate(true);	// �ʏ펞�X�V�ݒ�
			pPlayer->SetNormalDraw(true);	// �ʏ펞�`��ݒ�
			pPlayer->SetPoseDraw(true);		// �|�[�Y���`��ݒ�
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// �ʒu�������ʒu�ɖ߂�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// ���[�V�����ݒ�
			pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�

			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾
			pPlActiv->SetInUP(false);		// ����͐ݒ�
			pPlActiv->SetInDown(false);		// �����͐ݒ�
			pPlActiv->SetInLeft(false);		// �����͐ݒ�
			pPlActiv->SetInRight(false);	// �E���͐ݒ�

			float fPLSpeed = pPlayer->GetSpeed();
			m_fTutorialRange = fPLSpeed + fPLSpeed * 0.9f;

			//pPlayer->SetMove(false);

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

			//CFade::creat(CFade::TYPE::WHITE_IN, 30);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_000::~CStage_000()
		{

		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CStage_000::Update()
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �X�g���e�W�[�擾

			// �J�������v���C���[�ɒǏ]������Ȃ�
			if (m_bCameraFollowPlayer == true)
			{
				// �v���C���[���L��Ȃ�
				if (pPlayer != nullptr)
				{
					// �J�������v���C���[�ɒǏ]������
					pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_fCameraRot) * 300.0f, playerPos.z + cosf(m_fCameraRot) * 300.0f));	// �J�����ɓK��
				}
			}

			// �`���[�g���A���C�x���g����
			if (playerPos.z > s_fGool &&
				playerPos.z < s_fGool + 3.0f)
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			else if (playerPos.z > s_fTutorial_000 &&
				playerPos.z < s_fTutorial_000 + m_fTutorialRange)
			{
				if (m_bTutorial_000 == false)
				{
					pPlayer->SetMove(false);	// �������~�߂�
					pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
					pPlActiv->SetInLeft(true);		// �����͐ݒ�
					pPlActiv->SetInRight(true);	// �E���͐ݒ�

					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��

					m_bTutorial_000 = true;		// �t���O�𗧂Ă�
				}
			}
			else if (playerPos.z > s_fTutorial_001 &&
				playerPos.z < s_fTutorial_001 + m_fTutorialRange)
			{
				if (m_bTutorial_001 == false)
				{
					pPlayer->SetMove(false);	// �������~�߂�
					pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
					pPlActiv->SetInUP(true);		// ����͐ݒ�
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
					m_bTutorial_001 = true;		// �t���O�𗧂Ă�
				}
			}
			else if (playerPos.z > s_fTutorial_002 &&
				playerPos.z < s_fTutorial_002 + m_fTutorialRange)
			{
				if (m_bTutorial_002 == false)
				{
					pPlayer->SetMove(false);	// �������~�߂�
					pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
					pPlActiv->SetInDown(true);		// �����͐ݒ�
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
					m_bTutorial_002 = true;
				}
			}
			else if (playerPos.z > s_fTutorial_003 &&
				playerPos.z < s_fTutorial_003 + m_fTutorialRange)
			{
				if (m_bTutorial_003 == false)
				{
					pPlayer->SetMove(false);	// �������~�߂�
					pPlayer->SetMotionMove(false);	// ���[�V�����̓�����ݒ�
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(true);		// �|�b�v�A�b�v��\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(true);	// �|�b�v�A�b�v��\��
					m_bTutorial_003 = true;
				}
			}

			// �`���[�g���A���C�x���g
			if (m_bTutorial_000)
			{
				// ���ɓ��͂�����
				if (pKey->GetTrigger(DIK_A) ||
					pKey->GetTrigger(DIK_LEFT))
				{
					pPlayer->SetMove(true);			// ������
					pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
					pPlActiv->InputLeft();	// ������
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					m_bTutorial_000 = false;		// �t���O���~�낷
				}

				if(pKey->GetTrigger(DIK_D) ||
					pKey->GetTrigger(DIK_RIGHT))
				{
					pPlayer->SetMove(true);			// ������
					pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
					pPlActiv->InputRight();	// �E����
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					m_bTutorial_000 = false;		// �t���O���~�낷
				}
			}
			else if (m_bTutorial_001)
			{
				// ���ɓ��͂�����
				if (pKey->GetTrigger(DIK_W) ||
					pKey->GetTrigger(DIK_UP))
				{
					pPlayer->SetMove(true);			// ������
					pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
					pPlActiv->InputUP();	// �����
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					m_bTutorial_001 = false;		// �t���O���~�낷
				}
			}
			else if (m_bTutorial_002)
			{
				// �E�ɓ��͂�����
				if (pKey->GetTrigger(DIK_S) ||
					pKey->GetTrigger(DIK_DOWN))
				{
					pPlayer->SetMove(true);			// ������
					pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
					pPlActiv->InputDown();	// ������
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					m_bTutorial_002 = false;		// �t���O���~�낷
				}
			}
			else if (m_bTutorial_003)
			{
				// �������͂�����
				if (pKey->GetTrigger())
				{
					pPlayer->SetMove(true);			// ������
					pPlayer->SetMotionMove(true);	// ���[�V�����̓�����ݒ�
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(false);		// �|�b�v�A�b�v���\��
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(false);	// �|�b�v�A�b�v���\��
					m_bTutorial_003= false;		// �t���O���~�낷
				}
			}

			// �f�o�b�O���X�e�[�W�ڍs
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			return this;
		}
		void CStage_000::Draw() const
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_000::GetPose()
		{
			return false;
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_000>(CGameData* gamaData) {
			return new CStage_000(this, gamaData);
		}
	}
}