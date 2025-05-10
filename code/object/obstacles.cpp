//============================================
//
// �v���C���[[obstacles.cpp]
// Author:Uedakou
// 
//============================================
#include"obstacles.h"	// �I�u�W�F�N�g��Q��

/// <summary>
/// �R���X�g���N�^
/// </summary>
CObstacles::CObstacles()
{
	m_type = TYPE::TALL;	// ��ނ����ǂɂ��鍂��
	SetType(CObjectX::TYPE::OBSTACLES);	// ��ނ���Q���ɐݒ�
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
}
/// <summary>
/// �X�V
/// </summary>
void CObstacles::Update()
{
	CObjectX::Update();
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
	switch (type)
	{
	case TYPE::TALL:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_Tall.x");
		break;
	case TYPE::HIGH:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_High.x");
		break;
	case TYPE::LOW:
		nID = CModelX::Load("data/MODEL/Tentative/Obstacles_Low.x");
		break;
	default:
		break;
	}
	p->SetID(nID);

	return nullptr;
}

CObstacles::TALLUpdatStrateg::TALLUpdatStrateg()
{
}

CObstacles::TALLUpdatStrateg::~TALLUpdatStrateg()
{
}

CObstacles* CObstacles::TALLUpdatStrateg::update()
{
	return nullptr;
}

CObstacles::HIGHUpdatStrateg::HIGHUpdatStrateg()
{
}

CObstacles::HIGHUpdatStrateg::~HIGHUpdatStrateg()
{
}

CObstacles* CObstacles::HIGHUpdatStrateg::update()
{
	return nullptr;
}

CObstacles::LOWUpdatStrateg::LOWUpdatStrateg()
{
}

CObstacles::LOWUpdatStrateg::~LOWUpdatStrateg()
{
}

CObstacles* CObstacles::LOWUpdatStrateg::update()
{
	return nullptr;
}
