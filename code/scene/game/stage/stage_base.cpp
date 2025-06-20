//===========================================
// 
// �X�e�[�W000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_base.h"		// �X�e�[�W
#include "stage_000.h"		// �X�e�[�W000
#include "stage_001.h"		// �X�e�[�W001
#include "scene_debug.h"	// �X�e�[�W�f�o�b�O

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
#include "../../../object/scroll.h"	// �X�N���[��

#include <fstream>	// �t�@�C���̓ǂݍ��݂ɕK�v
#include <iostream>	// �t�@�C���̓ǂݍ��݂ɕK�v

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_Base::s_fCameraRot = 2.6f;	// �����v���C���[����̃J�����̊p�x
		const D3DXVECTOR3 CStage_Base::NumScrollPos = { 100.0f, 100.0f, 0.0f };	// �����v���C���[����̃J�����̊p�x
		const D3DXVECTOR3 CStage_Base::NumScrollSiz = { 100.0f, 100.0f, 0.0f };	// �����v���C���[����̃J�����̊p�x
		//============================================
		// �R���X�g
		//============================================
		CStage_Base::CStage_Base(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData),
			m_nNumScroll(0), m_nNumScrollOld(0), m_bPose(false) , m_bCameraFollowPlayer(true) , m_fGool(0)
		{
			m_fCameraRot = s_fCameraRot;
			m_pStrategy = new Stage_Play_Strategy(this);
			// �����擾���\��

			for (int nCnt = 0; nCnt < static_cast<int>(CGameData::Stage::MAX); nCnt++)
			{
				// �����̑傫�������炵�ĕ��ׂ�
				m_pNumScroll[nCnt] = CObject2D::creat(10, D3DXVECTOR3(NumScrollPos.x + NumScrollSiz.y * nCnt, NumScrollPos.y, NumScrollPos.z), NumScrollSiz);
				m_pNumScroll[nCnt]->SetTexture("data/TEXTURE/Scroll_000.png");
				m_pNumScroll[nCnt]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			}
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

			nsPrev::CBase* result = this;
			// �X�g���e�W�[���L������X�V����
			if (m_pStrategy != nullptr)
			{
				auto p = m_pStrategy->update(result);
				if (p != m_pStrategy)
				{
					delete m_pStrategy;
					m_pStrategy = p;
				}
			}
			if (m_nNumScroll != m_nNumScrollOld)
			{
				m_nNumScrollOld = m_nNumScroll;
				m_pNumScroll[m_nNumScrollOld]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			return result;
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
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pPrimary">�e</param>
		CStage_Base::Stage_Play_Strategy::Stage_Play_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
		}
		/// <summary>
		/// �ʏ�X�V�X�g���e�W
		/// </summary>
		/// <returns></returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Play_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾
			CCamera* pCamera = pManager->GetCamera();		// �J�����擾
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// �v���C���[�̈ʒu���擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �X�g���e�W�[�擾
			// �|�[�Y����
			if (pKey->GetTrigger(DIK_P))
			{
				m_pPrimary->m_bPose = !(m_pPrimary->m_bPose);
				// �|�[�Y������
				if (m_pPrimary->m_bPose)
				{
					// �v���C���[�̓������~�߂�
					pPlayer->SetMove(false);
				}
				// �|�[�Y������������
				else
				{
					// �v���C���[�𓮂���
					pPlayer->SetMove(true);
				}
			}
			if (m_pPrimary->m_bPose == false)
			{
				// �S�[������
				if (playerPos.z > m_pPrimary->m_fGool)
				{
					return new Stage_Goal_Strategy(m_pPrimary);
				}

				// �J�������v���C���[�ɒǏ]������Ȃ�
				if (m_pPrimary->m_bCameraFollowPlayer == true)
				{
					// �v���C���[���L��Ȃ�
					if (pPlayer != nullptr)
					{
						// �J�������v���C���[�ɒǏ]������
						pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_pPrimary->m_fCameraRot) * 300.0f, playerPos.z + cosf(m_pPrimary->m_fCameraRot) * 300.0f));	// �J�����ɓK��
					}
				}
			}
			// �����ƃv���C���[�̓����蔻��
			CObject* pObject[MAX_PRIORITY];
			CObject* pNext = nullptr;
			CObject::GetAllObject(pObject);
			for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			{
				while (pObject[nCnt] != nullptr)
				{
					pNext = pObject[nCnt]->GetNext();
					if (CScroll* pScroll = dynamic_cast<CScroll*>(pObject[nCnt]))
					{
						D3DXVECTOR3 PLpos = pPlayer->GetPos();	// �v���C���[�ʒu
						D3DXVECTOR3 PLcol = pPlayer->GetCollisionSiz();	// �v���C���[�R���W����
						D3DXVECTOR3 pos = pScroll->GetPos();	// �����ʒu
						D3DXVECTOR3 coll = pScroll->GetCollisionSiz();
						if (PLpos.z + PLcol.z * 0.5f > pos.z - coll.z * 0.5f &&
							PLpos.z - PLcol.z * 0.5f < pos.z + coll.z * 0.5f &&
							PLpos.x + PLcol.x * 0.5f > pos.x - coll.x * 0.5f &&
							PLpos.x - PLcol.x * 0.5f < pos.x + coll.x * 0.5f)
						{
							m_pPrimary->m_nNumScroll++;
							pScroll->Release();
						}
					}
					pObject[nCnt] = pNext;
				}
			}
			// �v���C���[�̗̑͂��O�ȉ��Ȃ�
			if (pPlayer->GetLife() <= 0)
			{
				return new Stage_Death_Strategy(m_pPrimary);
			}
#ifdef _DEBUG
			// �f�o�b�O���X�e�[�W�ڍs
			if (pKey->GetTrigger(DIK_L))
			{
				return new Stage_Goal_Strategy(m_pPrimary);
			}
#endif // !_DEBUG

			return this;
		}

		// �S�[�����X�g���e�W�[�萔
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_SelectPos{ SCREEN_W * 0.5f, SCREEN_H * 0.5f + 100.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_SelectSiz {100.0f, 100.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_PopupPos{ SCREEN_W * 0.5f, 200.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_PopupSiz {100.0f, 100.0f, 0.0f};
		/// <summary>
		/// �S�[�����R���X�g
		/// </summary>
		/// <param name="pPrimary">�e</param>
		CStage_Base::Stage_Goal_Strategy::Stage_Goal_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			pPlActiv->SetInUP(false);		// ����͐ݒ�
			pPlActiv->SetInDown(false);		// �����͐ݒ�
			pPlActiv->SetInLeft(false);		// �����͐ݒ�
			pPlActiv->SetInRight(false);	// �E���͐ݒ�

			// �X�N���[������ۑ�
			int nStage = 0;// �X�e�[�W
			if (dynamic_cast<CStage_000*>(this))nStage = 0;
			else if (dynamic_cast<CStage_001*>(this))nStage = 1;
			//else if(dynamic_cast<CStage_002*>(this))nStage = 1;



			// �X�N���[�������O��葽����Α���
			if (m_pPrimary->m_gameData->m_nScore[nStage] < m_pPrimary->m_nNumScroll)
			{
				m_pPrimary->m_gameData->m_nScore[nStage] = m_pPrimary->m_nNumScroll;
			}
			// �I��������
			m_nSelect = 0;
			m_nSelectOld = 0;

			// �I��������
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				m_pSelect[nCnt] = CObject2D::creat(6, D3DXVECTOR3(s_SelectPos.x, s_SelectPos.y + s_SelectSiz.x * nCnt, s_SelectPos.z), s_SelectSiz);
				switch (static_cast<SelectGoal>(nCnt))
				{
				case SelectGoal::StageSelect:	// �X�e�[�W�Z���N�g�ɖ߂�
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Select_StageSelect_000.png");
					break;
				case SelectGoal::ReTry:	// ���g���C
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Retry_000.png");
					break;
				default:
					break;
				}
			}
			// �I�𕨃J�[�\��
			m_pSelectBG = CObject2D::creat(5, m_pSelect[0]->GetPos(), m_pSelect[0]->GetSiz());

			// �|�b�v�A�b�v
			m_GoalPopup = CObject2D::creat(6, s_PopupPos, s_PopupSiz);// �|�b�v�A�b�v����
			m_GoalPopup->SetTexture("data/TEXTURE/StageClear_000.png");

			// �w�i
			m_BG = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));// �|�b�v�A�b�v����
			m_BG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		}

		/// <summary>
		/// �S�[�����f�X�g���N�^
		/// </summary>
		CStage_Base::Stage_Goal_Strategy::~Stage_Goal_Strategy()
		{
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

			pPlActiv->SetInUP(true);		// ����͐ݒ�
			pPlActiv->SetInDown(true);		// �����͐ݒ�
			pPlActiv->SetInLeft(true);		// �����͐ݒ�
			pPlActiv->SetInRight(true);	// �E���͐ݒ�
			// �Z���N�g���
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				if (m_pSelect[nCnt] != nullptr)
				{
					m_pSelect[nCnt]->Release();
					m_pSelect[nCnt] = nullptr;
				}
			}
			// �|�b�v�A�b�v���
			if (m_GoalPopup != nullptr)
			{
				m_GoalPopup->Release();
				m_GoalPopup = nullptr;
			}
		}
		/// <summary>
		/// �N���A�X�V
		/// </summary>
		/// <param name="owner">���V�[��</param>
		/// <returns>this�ȊO���̃X�g���e�W�[</returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Goal_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾

			m_nSelectOld = m_nSelect;	//���ʒu�ۑ�

			// ��I��
			if (pKey->GetTrigger(DIK_W) ||
				pKey->GetTrigger(DIK_UP))
			{
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = static_cast<int>(SelectGoal::MAX) - 1;
				}
			}
			// ���I��
			else if (pKey->GetTrigger(DIK_S) ||
				pKey->GetTrigger(DIK_DOWN))
			{
				m_nSelect++;
				if (m_nSelect >= static_cast<int>(SelectGoal::MAX))
				{
					m_nSelect = 0;
				}
			}
			// �I�����ύX���Ă�����
			if (m_nSelect != m_nSelectOld)
			{
				// �ʒu��ς���
				m_pSelectBG->SetPos(m_pSelect[m_nSelect]->GetPos());
			}

			if (pKey->GetTrigger(DIK_RETURN) ||
				pKey->GetTrigger(DIK_SPACE))
			{
				switch (static_cast<SelectGoal>(m_nSelect))
				{
				case SelectGoal::ReTry:	// ���g���C
					m_pPrimary;
					if (dynamic_cast<CStage_000*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_000>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CStage_001*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_001>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CSceneDebug*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CSceneDebug>(m_pPrimary->m_gameData);
					}
					break;
				case SelectGoal::StageSelect:	// �X�e�[�W�Z���N�g
					owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
					break;
				default:
					break;
				}
			}
			return this;
		}

		// ���S���X�g���e�W�[�萔
		const int CStage_Base::Stage_Death_Strategy::s_nPLMotionCnt = 30;
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_SelectPos{ SCREEN_W * 0.5f, SCREEN_H * 0.5f + 100.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_SelectSiz{ 100.0f, 100.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_PopupPos{ SCREEN_W * 0.5f, 200.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_PopupSiz{ 100.0f, 100.0f, 0.0f };
		/// <summary>
		/// ���S�X�g���e�W�[�R���X�g
		/// </summary>
		/// <param name="pPrimary">�e</param>
		CStage_Base::Stage_Death_Strategy::Stage_Death_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{

			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// �v���C���[�擾
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// �s���X�g���e�W�[�擾

						// �v���C���[�ݒ�
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_DEATH));	// ���[�V�����ݒ�
			pPlayer->SetMove(false);	// ������ݒ�

			pPlActiv->SetInUP(false);		// ����͐ݒ�
			pPlActiv->SetInDown(false);		// �����͐ݒ�
			pPlActiv->SetInLeft(false);		// �����͐ݒ�
			pPlActiv->SetInRight(false);	// �E���͐ݒ�

			// �X�N���[������ۑ�
			int nStage = 0;// �X�e�[�W
			if (dynamic_cast<CStage_000*>(this))nStage = 0;
			else if (dynamic_cast<CStage_001*>(this))nStage = 1;
			//else if(dynamic_cast<CStage_002*>(this))nStage = 1;



			// �X�N���[�������O��葽����Α���
			if (m_pPrimary->m_gameData->m_nScore[nStage] < m_pPrimary->m_nNumScroll)
			{
				m_pPrimary->m_gameData->m_nScore[nStage] = m_pPrimary->m_nNumScroll;
			}
			// �I��������
			m_nSelect = 0;
			m_nSelectOld = 0;

			// �I��������
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				m_pSelect[nCnt] = CObject2D::creat(6, D3DXVECTOR3(s_SelectPos.x, s_SelectPos.y + s_SelectSiz.x * nCnt, s_SelectPos.z), s_SelectSiz);
				switch (static_cast<SelectGoal>(nCnt))
				{
				case SelectGoal::StageSelect:	// �X�e�[�W�Z���N�g�ɖ߂�
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Select_StageSelect_000.png");
					break;
				case SelectGoal::ReTry:	// ���g���C
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Retry_000.png");
					break;
				default:
					break;
				}
			}
			// �I�𕨃J�[�\��
			m_pSelectBG = CObject2D::creat(5, m_pSelect[0]->GetPos(), m_pSelect[0]->GetSiz());

			// �|�b�v�A�b�v
			m_GoalPopup = CObject2D::creat(6, s_PopupPos, s_PopupSiz);// �|�b�v�A�b�v����
			m_GoalPopup->SetTexture("data/TEXTURE/StageClear_001.png");

			// �w�i
			m_BG = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));// �|�b�v�A�b�v����
			m_BG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		}
		/// <summary>
		/// ���S�X�g���e�W
		/// </summary>
		CStage_Base::Stage_Death_Strategy::~Stage_Death_Strategy()
		{
		}
		/// <summary>
		/// �X�g���e�W�[�X�V
		/// </summary>
		/// <param name="owner"></param>
		/// <returns></returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Death_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[�擾
			CInputKeyboard* pKey = pManager->GetInKey();	// �L�[�{�[�h���擾

			m_nSelectOld = m_nSelect;	//���ʒu�ۑ�

			// ��I��
			if (pKey->GetTrigger(DIK_W) ||
				pKey->GetTrigger(DIK_UP))
			{
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = static_cast<int>(SelectGoal::MAX) - 1;
				}
			}
			// ���I��
			else if (pKey->GetTrigger(DIK_S) ||
				pKey->GetTrigger(DIK_DOWN))
			{
				m_nSelect++;
				if (m_nSelect >= static_cast<int>(SelectGoal::MAX))
				{
					m_nSelect = 0;
				}
			}
			// �I�����ύX���Ă�����
			if (m_nSelect != m_nSelectOld)
			{
				// �ʒu��ς���
				m_pSelectBG->SetPos(m_pSelect[m_nSelect]->GetPos());
			}

			if (pKey->GetTrigger(DIK_RETURN) ||
				pKey->GetTrigger(DIK_SPACE))
			{
				switch (static_cast<SelectGoal>(m_nSelect))
				{
				case SelectGoal::ReTry:	// ���g���C
					m_pPrimary;
					if (dynamic_cast<CStage_000*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_000>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CStage_001*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_001>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CSceneDebug*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CSceneDebug>(m_pPrimary->m_gameData);
					}
					break;
				case SelectGoal::StageSelect:	// �X�e�[�W�Z���N�g
					owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
					break;
				default:
					break;
				}
			}

			if (m_nPLMotionCnt <= s_nPLMotionCnt)
			{
				m_nPLMotionCnt++;
				if (m_nPLMotionCnt == s_nPLMotionCnt)
				{
					CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// �v���C���[�擾
					pPlayer->SetMotionMove(false);
				}
			}
			return this;
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
					case 3:
						CScroll::clate(pos, rot);
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