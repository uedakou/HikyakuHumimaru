//============================================
//
// �v���C���[[player.cpp]
// Author:Uedakou
// 
//============================================
#include "player.h"	// �v���C���[
#include "../base/manager.h"	// �}�l�[�W���[
#include "enemy.h"	// �G�l�~�[
#include "../scene/scene_base.h"	// �V�[���x�[�X
#include <strsafe.h>
#include "collision/obb.h"		// OBB

#define PlayerMove true

const int CPlayer::s_nLife = 1;
const float CPlayer::s_fSpeed = 20.0f;
const bool CPlayer::s_bMove = true;
const float CPlayer::s_fLane = 500.0f;

//============================================
// �R���X�g
//============================================
CPlayer::CPlayer()
{
	SetLife(s_nLife);
	m_fSpeed = s_fSpeed;	// �������x�ݒ�
	m_bMove = s_bMove;
	m_fLane = s_fLane;

	//m_bJump = false;	// �W�����v�\��
	SetAttcak(1);

	CCharacter::SetType(CCharacter::TYPE::PLAYER);

	m_pActivityStrategy = new PlayerNomarActivity(this);

	m_pEffect = nullptr;
}
//============================================
// �f�X�g��
//============================================
CPlayer::~CPlayer()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect->DeathFlag();
		m_pEffect = nullptr;
	}
}
//============================================
// ������
//============================================
void CPlayer::Init()
{
	//m_obje[0] = CObjectX::creat(pos, rot, siz, CObjectX::TYPE_X_PLAYER);
	CObjectMotion::Load(PLAYER_MOTIONFILE_B);
	CCharacter::Init();
	CCharacter::SetCollisionX(PLAYER_SIZE);
	CObjectMotion::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	//SetMotion(1);
	SetLife(s_nLife);
	
}
//============================================
// �I��
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//============================================
// �X�V
//============================================
void CPlayer::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKey = pManager->GetInKey();


	// �d��
	AddMovePosY(-2.5f);
	D3DXVECTOR3 pos = GetPos();
	// �����ݒ�
	if (pos.y <= 0.0f)
	{
		SetPosY(0.0f);
		SetMovePosY(0.0f);
	}

	// �����ړ���true�Ȃ�
	if (m_bMove == true)
	{
		// m_fSpeed�i�߂�

		AddPosZ(m_fSpeed);
	}

	// ���ɓ��͂�����
	if (pKey->GetTrigger(DIK_W) ||
		pKey->GetTrigger(DIK_UP))
	{
		m_pActivityStrategy->InputUP();
	}
	// �E�ɓ��͂�����
	else if (pKey->GetTrigger(DIK_S) ||
		pKey->GetTrigger(DIK_DOWN))
	{
		m_pActivityStrategy->InputDown();
	}
	// ���ɓ��͂�����
	else if (pKey->GetTrigger(DIK_A) ||
		pKey->GetTrigger(DIK_LEFT))
	{
		m_pActivityStrategy->InputLeft();
	}
	// �E�ɓ��͂�����
	else if (pKey->GetTrigger(DIK_D) ||
		pKey->GetTrigger(DIK_RIGHT))
	{
		m_pActivityStrategy->InputRight();
	}



	CCharacter::Update();
}
//============================================
// �`��
//============================================
void CPlayer::Draw()
{
	CCharacter::Draw();
}
//============================================
// �q�b�g����
//============================================
void CPlayer::Hit(int nDamage)
{
	CCharacter::Hit(nDamage);
	if (GetLife() <= 0)
	{
		
		
	}
}
void CPlayer::Hit(int nCntInvincible, int nDamage)
{
}
void CPlayer::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
}
//============================================
// ����
//============================================
CPlayer* CPlayer::creat()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}
//============================================
// �ړ�����
//============================================
void CPlayer::MoveAttenuation()
{
	CCharacter::MoveAttenuation();
}
//============================================
// ���[�v���Ȃ����[�V�����̎��̃��[�V����
//============================================
int CPlayer::GetNextMotion()
{
	D3DXVECTOR3 move = GetMovePos();
	if (GetLife() <= 0)
	{
		return static_cast<int>(Motion::ACTIVITY_DETHILoop); ;
	}
	else
	{
		if (move.x > 0.5f)
		{
			return static_cast<int>(Motion::ACTIVITY_MOVE);
		}
	}

	return static_cast<int>(Motion::ACTIVITY_NEUTRAL);
}
/// <summary>
/// �ʏ펞�X�g���e�W�[�R���X�g���N�^
/// </summary>
/// <param name="player"></param>
CPlayer::PlayerNomarActivity::PlayerNomarActivity(CPlayer* player):
	ActivityStrategy(player)
{
	m_type = TYPE::NORMAL;	//�@��ނ�ʏ�ɐݒ�
}
/// <summary>
/// �ʏ펞�X�g���e�W�[�f�X�g���N�^
/// </summary>
CPlayer::PlayerNomarActivity::~PlayerNomarActivity()
{
}

void CPlayer::PlayerNomarActivity::InputUP()
{
	if (m_bInUP)
	{

	}
}

void CPlayer::PlayerNomarActivity::InputDown()
{
	if (m_bInDown)
	{

	}
}

void CPlayer::PlayerNomarActivity::InputLeft()
{
	if (m_bInLeft)
	{
		m_pPrimary->AddPosX(-m_pPrimary->m_fLane);	// ���Ɉړ�
		float posX = m_pPrimary->GetPosX();	// �v���C���[�̈ʒu�擾
		// �v���C���[�����[���O�ɏo�Ă�����
		if (posX < -m_pPrimary->m_fLane)
		{
			// ���ɖ߂�
			m_pPrimary->SetPosX(-m_pPrimary->m_fLane);
		}
	}
}

void CPlayer::PlayerNomarActivity::InputRight()
{
	if (m_bInRight)
	{
		m_pPrimary->AddPosX(m_pPrimary->m_fLane);	// �E�Ɉړ�
		float posX = m_pPrimary->GetPosX();	// �v���C���[�̈ʒu�擾
		// �v���C���[�����[���O�ɏo�Ă�����
		if (posX > m_pPrimary->m_fLane)
		{
			// ���ɖ߂�
			m_pPrimary->SetPosX(m_pPrimary->m_fLane);
		}
	}
}