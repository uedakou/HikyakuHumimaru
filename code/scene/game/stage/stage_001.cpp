//===========================================
// 
// �X�e�[�W000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_001.h"		// �X�e�[�W

#include "../../../object/player.h"	// �v���C���[
#include "../../../object/base/object_2D.h"	// �|�b�v�A�b�v�p2D
#include "../../../object/base/object_3D.h"	// �|�b�v�A�b�v�p3D
#include "../../../object/base/object_X.h"	// �|�b�v�A�b�v�pX
#include "../../../object/base/object_fade.h"	// �t�F�[�h
#include "../../../object/base/object_billboard.h"	// �r���{�[�h
#include "../game_data.h"	// �Q�[���f�[�^
#include "../../../object/base/text.h"	// �e�L�X�g
#include "../../../object/obstacles_tall.h"	// ��Q��
#include "../../../object/obstacles_high.h"	// ��Q��
#include "../../../object/obstacles_low.h"	// ��Q��

#include <fstream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include <iostream>	// �t�@�C���̓ǂݍ��݂ɕK�v

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_001::s_fGool = 20000.0f;	// �S�[������
		const string CStage_001::s_aStage = "data/STAGE/Stage_001.txt";		// �X�e�[�W�p�X

		//============================================
		// �R���X�g
		//============================================
		CStage_001::CStage_001(CBase* scene, CGameData* gameData) :
			CStage_Base(scene, gameData)
		{
			CObject::ReleaseScene();	// �V�[�������[�X
			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾

			// �����o�ϐ��ݒ�
			m_bPose = false;

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

			//�t�B�[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Load_000.png");

			// �X�e�[�W�ǂݍ���
			Load(s_aStage);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_001::~CStage_001()
		{
			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			pPlActiv->SetInUP(true);		// ����͐ݒ�
			pPlActiv->SetInDown(true);		// �����͐ݒ�
			pPlActiv->SetInLeft(true);		// �����͐ݒ�
			pPlActiv->SetInRight(true);	// �E���͐ݒ�
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CStage_001::Update()
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �X�g���e�W�[�擾

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
				// �`���[�g���A���C�x���g����
				if (playerPos.z > s_fGool)
				{
					return makeScene<CScen_Game_StageSelect>(m_gameData);
				}
			}
			// �v���C���[�̗̑͂��O�ȉ��Ȃ�
			if (pPlayer->GetLife() <= 0)
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#ifdef _DEBUG
			// �f�o�b�O���X�e�[�W�ڍs
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#endif // !_DEBUG

			CStage_Base::Update();

			return this;
		}
		void CStage_001::Draw() const
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_001::GetPose()
		{

			CStage_Base::Draw();

			return m_bPose;
		}
		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_001>(CGameData* gamaData) {
			return new CStage_001(this, gamaData);
		}
	}
}