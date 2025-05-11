//============================================
//
// �v���C���[[obstacles.cpp]
// Author:Uedakou
// 
//============================================
#include"obstacles.h"	// �I�u�W�F�N�g��Q��
#include "player.h"		// �v���C���[
#include "base/character.h"	// �L�����N�^�[
/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstacles::CObstacles()
{
	m_type = TYPE::TALL;	// ��ނ����ǂɂ��鍂��
	SetType(CObjectX::TYPE::OBSTACLES);	// ��ނ���Q���ɐݒ�
	m_pHitStrateg = new HitStrateg();
	
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CObstacles::~CObstacles()
{
}
/// <summary>
/// ����������
/// </summary>
void CObstacles::Init()
{
	CObjectX::Init();
}
/// <summary>
/// �I������
/// </summary>
void CObstacles::Uninit()
{
	CObjectX::Uninit();

	if (m_pHitStrateg != nullptr)
	{
		delete m_pHitStrateg;
		m_pHitStrateg = nullptr;
	}
}
/// <summary>
/// �X�V
/// </summary>
void CObstacles::Update()
{
	CObjectX::Update();
	if (m_pHitStrateg != nullptr)
	{

		CObject* pObject[MAX_PRIORITY];
		CObject* pNext = nullptr;
		CObject::GetAllObject(pObject);
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			while (pObject[nCnt] != nullptr)
			{
				pNext = pObject[nCnt]->GetNext();
				CPlayer* player = static_cast<CPlayer*>(pObject[nCnt]);
				if (player)
				{
					bool a;
					a = player->IsMove();
					a = false;
				}
				pObject[nCnt] = pNext;
			}
		}
	}

}
/// <summary>
/// �`��
/// </summary>
void CObstacles::Draw()
{
	CObjectX::Draw();
}
/// <summary>
/// ��Q������
/// </summary>
/// <param name="type">��Q���̎��</param>
/// <param name="pos">��Q���̈ʒu</param>
/// <returns>����������Q���̃|�C���^�[</returns>
CObstacles* CObstacles::clate(TYPE type, D3DXVECTOR3 pos)
{
	CObstacles* p = new CObstacles();
	p->SetPos(pos);	// �ʒu�ݒ�
	p->m_type = type;	// ��ސݒ�
	int nID = 0;	// ���f��ID�ۑ��p
	if (p->m_pHitStrateg != nullptr)
	{
		delete p->m_pHitStrateg;
		p->m_pHitStrateg = nullptr;
	}
	switch (type)
	{
	case TYPE::TALL:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_Tall.x");
		p->m_pHitStrateg = new TallHitStrateg();
		break;
	case TYPE::HIGH:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_High.x");
		p->m_pHitStrateg = new HighHitStrateg();
		break;
	case TYPE::LOW:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_Low.x");
		p->m_pHitStrateg = new LowHitStrateg();
		break;
	default:
		break;
	}
	p->SetID(nID);

	return nullptr;
}

/// <summary>
/// �w�̍�����Q���R���X�g���N�^
/// </summary>
/// <param name="pPrimary">�e</param>
CObstacles::TallHitStrateg::TallHitStrateg()
{
}
/// <summary>
/// �w�̍�����Q���f�X�g���N�^
/// </summary>
CObstacles::TallHitStrateg::~TallHitStrateg()
{
}
/// <summary>
/// �w�̍�����Q���q�b�g����
/// </summary>
void CObstacles::TallHitStrateg::update(CPlayer* pPlayer)
{

}
/// <summary>
/// �����ʒu�̏�Q���R���X�g���N�^
/// </summary>
/// <param name="pPrimary">�e</param>
CObstacles::HighHitStrateg::HighHitStrateg()
{
}
/// <summary>
/// �����ʒu�̏�Q���f�X�g���N�^
/// </summary>
CObstacles::HighHitStrateg::~HighHitStrateg()
{
}
/// <summary>
/// �����ʒu�̏�Q���q�b�g����
/// </summary>
void CObstacles::HighHitStrateg::update(CPlayer* pPlayer)
{

}
/// <summary>
/// �Ⴂ�ʒu�̏�Q���R���X�g���N�^
/// </summary>
/// <param name="pPrimary">�e</param>
CObstacles::LowHitStrateg::LowHitStrateg()
{
}
/// <summary>
/// �Ⴂ�ʒu�̏�Q���f�X�g���N�^
/// </summary>
CObstacles::LowHitStrateg::~LowHitStrateg()
{
}
/// <summary>
/// �Ⴂ�ʒu�̏�Q���q�b�g����
/// </summary>
void CObstacles::LowHitStrateg::update(CPlayer* pPlayer)
{

}
