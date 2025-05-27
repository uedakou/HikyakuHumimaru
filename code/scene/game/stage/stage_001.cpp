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

		const bool CStage_001::s_bCameraFollowPlayer = true;	// �J�������v���C���[��Ǐ]���邩�ǂ���
		const float CStage_001::s_fCameraRot = 2.6f;	// �v���C���[����̃J�����̊p�x
		const float CStage_001::s_fGool = 20000.0f;	// �S�[������
		const string CStage_001::s_aStage = "data/STAGE/Stage_001.txt";		// �X�e�[�W�p�X

		//============================================
		// �R���X�g
		//============================================
		CStage_001::CStage_001(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// �V�[�������[�X
			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾

			// �����o�ϐ��ݒ�
			m_bPose = false;
			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// �J�������v���C���[��Ǐ]���邩�ǂ���
			m_fCameraRot = s_fCameraRot;	// �v���C���[����̃J�����̊p�x

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

			// �X�e�[�W�ǂݍ���
			//Load();
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
			}
#ifdef _DEBUG
			// �f�o�b�O���X�e�[�W�ڍs
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#endif // !_DEBUG
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
			return m_bPose;
		}
		/// <summary>
		/// �X�e�[�W�ǂݍ���
		/// </summary>
		void CStage_001::Load()
		{
			ifstream file(s_aStage.c_str());  // �ǂݍ��ރt�@�C���̃p�X���w��
			if (file.fail()) {
				cerr << "�t�@�C�����J���܂���ł���\n";
			}
			string str0, str1, str2, str3;	// ������i�[�p
			string skip;			// �X�L�b�v�p�i�[
			string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

		// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
			while (file >> str0)
			{
				// �R�����g�A�E�g
				if (str0[0] == '#')
				{
					getline(file, skip);	// ��s�X�L�b�v
				}
				// ��Q��TALL
				else if (str0.compare("OBSTACLES") == 0)
				{
					while (file >> str1 &&
						str1.compare("END_OBSTACLES_") != 0)
					{






					}
				}
			}
			// �t�@�C�������
			file.close();
		}
		/// <summary>
		/// ���}�b�v�z�u
		/// </summary>
		void CStage_001::LoadT()
		{
			// ���[���h����
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetTexture("data/TEXTURE/Provisional/Glass000.png");
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