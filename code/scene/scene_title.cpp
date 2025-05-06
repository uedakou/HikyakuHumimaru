//===========================================
// 
// �^�C�g���V�[��[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#include "scene_title.h"	// �^�C�g���V�[��
//#include "common_data.h"	// ���L�f�[�^
#include "../base/manager.h"		// �S�̃}�l�[�W���[
#include "../object/base/object_2D.h"		// �I�u�W�F�N�g�QD
#include "../object/base/object_fade.h"
#include "../object/base/object_billboard.h"

namespace Scene {
	namespace Game {
		class CGameManager;
	}
	class CSceneDebug;

	const D3DXCOLOR CTitle::m_Selected = {1.0f, 0.0f, 0.0f, 1.0f};		// �I��
	const D3DXCOLOR CTitle::m_NotSelected = { 1.0f, 1.0f, 1.0f, 1.0f};	// ��I��

	//============================================
	// �R���X�g���N�^
	//============================================
	CTitle::CTitle(CBase* scene) :
		CBase(*scene),
		m_nCntMax(30)
	{
		CObject::ReleaseScene();
		CManager* manager = CManager::GetInstance();	// �}�l�[�W���[
		CCamera* pCamera = manager->GetCamera();
		//pCamera->SetNomal();

		srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();

		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_TITLE000);

		m_nCnt = 0;

		// �w�i
		m_pBG = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0));	// ����
		m_pBG->SetTexture("data/TEXTURE/Provisional/BG_000.png");	// �e�N�X�`��
		m_pBG->SetType(CObject2D::TYPE::BG);	// ��ނ�w�i�ɐݒ�

		// �^�C�g��
		m_pTitle = CObject2D::creat(4, D3DXVECTOR3(300.0f, 150.0f, 0.0f), D3DXVECTOR3(500.0f, 200.0f, 0));	// ����
		m_pTitle->SetTexture("data/TEXTURE/Provisional/Title_000.png");	// �e�N�X�`��
		m_pTitle->SetType(CObject2D::TYPE::POPUP);	// ��ނ��|�b�v�A�b�v�ɐݒ�

		// �Z���N�g
		m_nSelect = 0;	// ���݂̑I��
		for (int nCnt = 0; nCnt < static_cast<int>(SELECT_TYPE::MAX); nCnt++)
		{
			m_pOptions[nCnt] = CObject2D::creat(5,
				D3DXVECTOR3(SCREEN_W * 0.5f, 500.0f + (nCnt * 100.0f), 0),
				D3DXVECTOR3(200.0f, 90.0f, 0));
			switch (static_cast<SELECT_TYPE>(nCnt))
			{
			case SELECT_TYPE::STATE:
				m_pOptions[nCnt]->SetTexture("data/TEXTURE/Provisional/Start_000.png");
				break;
			case SELECT_TYPE::END:
				m_pOptions[nCnt]->SetTexture("data/TEXTURE/Provisional/End_000.png");
				break;
			default:
				break;
			}

		}

		m_pSelectedOption = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, 500.0f , 0),D3DXVECTOR3(210.0f, 100.0f, 0));
		m_pSelectedOption->SetColor(m_Selected);	// �I�𒆂̐F�ݒ�
		//m_pSelectedOption->SetTexture("d+ata/TEXTURE/Provisional/End_000.png");

		m_bNext = false;

		CFade::creat(CFade::TYPE::WHITE_IN, m_nCntMax);

	}
	//============================================
	// �f�X�g��
	//============================================
	CTitle::~CTitle()
	{
		CManager* pManager = CManager::GetInstance();	// �}�l�[�W���[
		CSound* pSound = pManager->GetSound();	// �T�E���h
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_TITLE000);	// BGM���~�߂�
		// �^�C�g��
		if (m_pTitle != nullptr)
		{
			m_pTitle = nullptr;
		}
		// �Z���N�g
		for (int nCnt = 0; nCnt < static_cast<int>(SELECT_TYPE::MAX); nCnt++ )
		{
			if (m_pOptions[nCnt] != nullptr)
			{
				m_pOptions[nCnt] = nullptr;
			}
		}
	}
	//============================================
	// �X�V
	//============================================
	CBase* CTitle::Update()
	{
		CManager* pManager = CManager::GetInstance();
		CInputKeyboard* pKye = pManager->GetInKey();
		CSound* pSound = pManager->GetSound();

		int nSelectOld = m_nSelect;
		// �G���^�[���܂������ĂȂ�������
		if (m_bNext == false)
		{
			// �G���^�[����������
			if (pKye->GetTrigger(DIK_RETURN))
			{
				// �t�F�[�h�Ǝ��V�[���ւ̃t���O�𗧂Ă�
				m_bNext = true;
			}
			// W����������
			if (pKye->GetTrigger(DIK_W))
			{
				// �Z���N�g����グ��
				m_nSelect--;
				// ��ԏ�Ȃ�ŉ��i�ɂ���
				if (m_nSelect < 0)
				{
					m_nSelect = static_cast<int>(SELECT_TYPE::MAX) - 1;
				}
			}
			// S����������
			else if (pKye->GetTrigger(DIK_S))
			{
				// �Z���N�g���������
				m_nSelect++;
				// ��ԉ��Ȃ�ŏ�i�ɂ���
				if (m_nSelect >= static_cast<int>(SELECT_TYPE::MAX))
				{
					m_nSelect = 0;
				}
			}
			// �Z���N�g��ύX���Ă�����F��ύX����
			if (nSelectOld != m_nSelect)
			{
				D3DXVECTOR3 pos = m_pOptions[m_nSelect]->GetPos();
				m_pSelectedOption->SetPos(pos);
				if (m_pOptions[nSelectOld] != nullptr)
				{
					m_pOptions[nSelectOld]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
				}
				if (m_pOptions[m_nSelect] != nullptr)
				{
					m_pOptions[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
				}
			}
		}
		// ���V�[���ւ̃t���O�������Ă�����
		else
		{
			// �J�E���g�J�n�Ȃ�
			if (m_nCnt == 0)
			{
				// �t�F�[�h�J�n
				CFade::creat(10, CFade::TYPE::WHITE_OUT, m_nCntMax);
			}
			// �J�E���g���ő�܂Ői�񂾂�
			if (m_nCnt >= m_nCntMax)
			{
				// �I�����Ă��鏈��������
				switch (static_cast<SELECT_TYPE>(m_nSelect))
				{
				case SELECT_TYPE::STATE:
					// �Q�[���X�^�[�g
					return makeScene<Game::CGameManager>();
					break;
				case SELECT_TYPE::END:
					// �I��
					return nullptr;
					break;
				default:
					break;
				}
			}
			// �V�[���ύX�̃J�E���g������
			m_nCnt++;
		}

		CObject* Top[MAX_PRIORITY];
		CObject::GetAllObject(Top);
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			CObject* pObject = Top[nCnt];
			CObject* pNext = nullptr;
			while (pObject != nullptr)
			{
				pNext = pObject->GetNext();

				if (pObject->GetType() == CObject::TYPE::BILLBOARD)
				{

					CObjectBillbord* pTree = (CObjectBillbord*)pObject;
					pTree->AddPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f));


					D3DXVECTOR3 pos = pTree->GetPos();
					if (pos.z <= -500.0f)
					{
						pTree->DeathFlag();
					}

				}
				pObject = pNext;
			}
		}


		return this;
	}
	//============================================
	// �`��
	//============================================
	void CTitle::Draw() const
	{

	}
	//============================================
	// �|�[�Y���擾
	//============================================
	bool CTitle::GetPose()
	{
		return false;
	}
	//============================================
	// �V�[������
	//============================================
	template<>
	CBase* CBase::makeScene<CTitle>() {
		return new CTitle(this);
	}
}