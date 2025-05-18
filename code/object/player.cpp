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
	CObjectMotion::Load(PLAYER_MOTIONFILE_A);
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
		//�n�ʂɂ��Ă���Ƃ��W�����v���[�V�����Ȃ�
		int nMotion = GetMotion();
		if (nMotion == static_cast<int>(Motion::ACTIVITY_JANP))
		{
			// ���胂�[�V�����ɐݒ�
			SetMotion(static_cast<int>(Motion::ACTIVITY_MOVE));
		}
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
		// ���S���[�V����
		//return static_cast<int>(Motion::ACTIVITY_DETHILoop); ;
	}
	else
	{
		if (GetMotion() == static_cast<int>(Motion::ACTIVITY_JANP))
		{
			return static_cast<int>(Motion::ACTIVITY_MOVE);
		}
	}

	return static_cast<int>(Motion::ACTIVITY_NEUTRAL);
}
/// <summary>
/// �ʏ펞�X�g���e�W�[�R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
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
/// <summary>
/// �X�V
/// </summary>
/// <returns>this�ӊO���̃X�g���e�W�[</returns>
CPlayer::PlayerNomarActivity* CPlayer::PlayerNomarActivity::Update()
{
	return this;
}
/// <summary>
/// �ʏ펞�W�����v���͏���
/// </summary>
void CPlayer::PlayerNomarActivity::InputUP()
{
	if (m_bInUP)
	{
		m_pPrimary->AddMovePosY(20.0f);
		m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_JANP));
	}
}
/// <summary>
/// �ʏ펞�X���C�f�B���O����
/// </summary>
void CPlayer::PlayerNomarActivity::InputDown()
{
	if (m_bInDown)
	{
		m_pPrimary->AddMovePosY(20.0f);
		m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_SLIDING));
	}
}
/// <summary>
/// �ʏ펞�����͏���
/// </summary>
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
/// <summary>
/// �ʏ펞���͉E����
/// </summary>
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
/// <summary>
/// �W�����v���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerJanpActivity::PlayerJanpActivity(CPlayer* player) :
	ActivityStrategy(player)
{
}
/// <summary>
/// �W�����v���f�X�g���N�^
/// </summary>
CPlayer::PlayerJanpActivity::~PlayerJanpActivity()
{
}
/// <summary>
/// �W�����v���X�V
/// </summary>
/// <returns></returns>
CPlayer::PlayerJanpActivity* CPlayer::PlayerJanpActivity::Update()
{
	return this;
}
/// <summary>
/// �W�����v���W�����v����
/// </summary>
void CPlayer::PlayerJanpActivity::InputUP()
{
}
// �W�����v���X���C�f�B���O����
void CPlayer::PlayerJanpActivity::InputDown()
{
}
/// <summary>
/// �W�����v��������
/// </summary>
void CPlayer::PlayerJanpActivity::InputLeft()
{
}
/// <summary>
/// �W�����v���E����
/// </summary>
void CPlayer::PlayerJanpActivity::InputRight()
{
}
/// <summary>
/// �X���C�f�B���O���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerSlidingActivity::PlayerSlidingActivity(CPlayer* player) :
	ActivityStrategy(player)

{
}
/// <summary>
/// �X���C�f�B���O���f�X�g���N�^
/// </summary>
CPlayer::PlayerSlidingActivity::~PlayerSlidingActivity()
{
}
/// <summary>
/// �X���C�e�B���O���A�b�v�f�[�g
/// </summary>
/// <returns></returns>
CPlayer::PlayerSlidingActivity* CPlayer::PlayerSlidingActivity::Update()
{
	return this;
}
/// <summary>
/// �X���C�f�B���O���W�����v����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputUP()
{
}
/// <summary>
/// �X���C�f�B���O���X���C�e�B���O����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputDown()
{
}
/// <summary>
/// �X���C�f�B���O��������
/// </summary>
void CPlayer::PlayerSlidingActivity::InputLeft()
{
}
/// <summary>
/// �X���C�f�B���O���E����
/// </summary>
void CPlayer::PlayerSlidingActivity::InputRight()
{
}
/// <summary>
/// ���[���`�F���W���R���X�g���N�^
/// </summary>
/// <param name="player">�e</param>
CPlayer::PlayerLaneChangeActivity::PlayerLaneChangeActivity(CPlayer* player) :
	ActivityStrategy(player)

{
}
/// <summary>
/// ���[���`�F���W���f�X�g���N�^
/// </summary>
CPlayer::PlayerLaneChangeActivity::~PlayerLaneChangeActivity()
{
}
/// <summary>
/// ���[���`�F���W���X�V
/// </summary>
/// <returns></returns>
CPlayer::PlayerLaneChangeActivity* CPlayer::PlayerLaneChangeActivity::Update()
{
	return this;
}
/// <summary>
/// ���[���`�F���W���W�����v����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputUP()
{
}
/// <summary>
/// ���[���`�F���W���X���C�e�B���O����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputDown()
{
}
/// <summary>
/// ���[���`�F���W��������
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputLeft()
{
}
/// <summary>
/// ���[���`�F���W���E����
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputRight()
{
}
