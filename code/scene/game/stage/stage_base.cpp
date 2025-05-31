//===========================================
// 
// �X�e�[�W000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_base.h"		// �X�e�[�W

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

		const float CStage_Base::s_fCameraRot = 2.6f;	// �����v���C���[����̃J�����̊p�x
		//============================================
		// �R���X�g
		//============================================
		CStage_Base::CStage_Base(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			m_bPose = false;
			m_bCameraFollowPlayer = true;
			m_fCameraRot = s_fCameraRot;
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_Base::~CStage_Base()
		{
		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CStage_Base::Update()
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
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
		void CStage_Base::Draw() const
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_Base::GetPose()
		{
			return m_bPose;
		}
		/// <summary>
		/// �X�e�[�W�ǂݍ���
		/// </summary>
		void CStage_Base::Load(const string& filePath)
		{
			ifstream file(filePath.c_str());  // �ǂݍ��ރt�@�C���̃p�X���w��
			if (file.fail()) {
				MessageBoxA(nullptr, "�J���܂���ł���", "�G���[", MB_OK);
			}
			string str0, str1, str2, str3;	// ������i�[�p
			string _;	// �X�L�b�v�p�i�[
			string aModelFile[MAX_MOTION_MODEL];	// ���f���t�@�C��

		// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
			while (file >> str0)
			{
				// �R�����g�A�E�g
				if (str0[0] == '#')
				{
					getline(file, _);	// ��s�X�L�b�v
				}
				// ��Q��TALL
				else if (str0.compare("OBSTACLES") == 0)
				{
					int nType = 0;	// ���
					D3DXVECTOR3 pos = {};	// �ʒu
					D3DXVECTOR3 rot = {};	// ����


					while (file >> str1 &&
						str1.compare("END_OBSTACLES") != 0)
					{
						// �R�����g�A�E�g
						if (str1[0] == '#')
						{
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							nType = atoi(str2.c_str());
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							pos.x = stof(str2.c_str());
							file >> str2;	// ���f�������擾
							pos.y = stof(str2.c_str());
							file >> str2;	// ���f�������擾
							pos.z = stof(str2.c_str());
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// ���f�������擾
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// ���f�������擾
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// ��s�X�L�b�v
						}
					}
					// ��Q������
					switch (nType)
					{
					case 0:
						CObstaclesToll::clate(pos, rot);
						break;
					case 1:
						CObstaclesHigh::clate(pos, rot);
						break;
					case 2:
						CObstaclesLow::clate(pos, rot);
						break;
					default:
#ifdef _DEBUG
						OutputDebugStringA("�f�o�b�O�o�́F���݂��Ȃ���Q���𐶐����悤�Ƃ��܂����B\n");
						Beep(1200, 300);
#endif // _DEBUG
						break;
					}

				}
				else if (str0.compare("OBJECT") == 0)
				{
					int nType = 0;	// ���
					D3DXVECTOR3 pos = {};	// �ʒu
					D3DXVECTOR3 rot = {};	// ����
					CObjectX* pObject = nullptr;	// �I�u�W�F�N�g

					while (file >> str1 &&
						str1.compare("END_OBJECT") != 0)
					{
						// �R�����g�A�E�g
						if (str1[0] == '#')
						{
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							nType = atoi(str2.c_str());
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							pos.x = stof(str2.c_str());
							file >> str2;	// ���f�������擾
							pos.y = stof(str2.c_str());
							file >> str2;	// ���f�������擾
							pos.z = stof(str2.c_str());
							getline(file, _);	// ��s�X�L�b�v
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// �ꕶ�X�L�b�v
							file >> str2;	// ���f�������擾
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// ���f�������擾
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// ���f�������擾
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// ��s�X�L�b�v
						}
					}	/* !while (file >> str1 &&
					str1.compare("END_OBSTACLES") != 0)*/
					// ��ޕʐ���
					if (nType == 0)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_000.x");
					}
					else if (nType == 1)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_001.x");
					}
					else
					{
						OutputDebugStringA("�f�o�b�O�o�́F���݂��Ȃ��I�u�W�F�N�g�𐶐����悤�Ƃ��܂����B\n");
						Beep(1200, 300);
					}
					if (pObject != nullptr)
					{
						pObject->SetPos(pos);
						pObject->SetRot(rot);
					}

				}
			}
			// �t�@�C�������
			file.close();
		}
	}
}