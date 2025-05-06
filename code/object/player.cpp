//============================================
//
// プレイヤー[player.cpp]
// Author:Uedakou
// 
//============================================
#include "player.h"	// プレイヤー
#include "../base/manager.h"	// マネージャー
#include "enemy.h"	// エネミー
#include "../scene/scene_base.h"	// シーンベース
#include <strsafe.h>
#include "collision/obb.h"		// OBB

#define PlayerMove true

const int CPlayer::s_nLife = 1;
const float CPlayer::s_fSpeed = 20.0f;
const bool CPlayer::s_bMove = true;
const float CPlayer::s_fLane = 500.0f;

//============================================
// コンスト
//============================================
CPlayer::CPlayer()
{
	SetLife(s_nLife);
	m_fSpeed = s_fSpeed;	// 初期速度設定
	m_bMove = s_bMove;
	m_fLane = s_fLane;

	//m_bJump = false;	// ジャンプ可能か
	SetAttcak(1);

	CCharacter::SetType(CCharacter::TYPE::PLAYER);

	m_pActivityStrategy = new PlayerNomarActivity(this);

	m_pEffect = nullptr;
}
//============================================
// デストラ
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
// 初期化
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
// 終了
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//============================================
// 更新
//============================================
void CPlayer::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKey = pManager->GetInKey();


	// 重力
	AddMovePosY(-2.5f);
	D3DXVECTOR3 pos = GetPos();
	// 下限設定
	if (pos.y <= 0.0f)
	{
		SetPosY(0.0f);
		SetMovePosY(0.0f);
	}

	// 自動移動がtrueなら
	if (m_bMove == true)
	{
		// m_fSpeed進める

		AddPosZ(m_fSpeed);
	}

	// 左に入力したら
	if (pKey->GetTrigger(DIK_W) ||
		pKey->GetTrigger(DIK_UP))
	{
		m_pActivityStrategy->InputUP();
	}
	// 右に入力したら
	else if (pKey->GetTrigger(DIK_S) ||
		pKey->GetTrigger(DIK_DOWN))
	{
		m_pActivityStrategy->InputDown();
	}
	// 左に入力したら
	else if (pKey->GetTrigger(DIK_A) ||
		pKey->GetTrigger(DIK_LEFT))
	{
		m_pActivityStrategy->InputLeft();
	}
	// 右に入力したら
	else if (pKey->GetTrigger(DIK_D) ||
		pKey->GetTrigger(DIK_RIGHT))
	{
		m_pActivityStrategy->InputRight();
	}



	CCharacter::Update();
}
//============================================
// 描画
//============================================
void CPlayer::Draw()
{
	CCharacter::Draw();
}
//============================================
// ヒット処理
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
// 生成
//============================================
CPlayer* CPlayer::creat()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}
//============================================
// 移動減衰
//============================================
void CPlayer::MoveAttenuation()
{
	CCharacter::MoveAttenuation();
}
//============================================
// ループしないモーションの次のモーション
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
/// 通常時ストラテジーコンストラクタ
/// </summary>
/// <param name="player"></param>
CPlayer::PlayerNomarActivity::PlayerNomarActivity(CPlayer* player):
	ActivityStrategy(player)
{
	m_type = TYPE::NORMAL;	//　種類を通常に設定
}
/// <summary>
/// 通常時ストラテジーデストラクタ
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
		m_pPrimary->AddPosX(-m_pPrimary->m_fLane);	// 左に移動
		float posX = m_pPrimary->GetPosX();	// プレイヤーの位置取得
		// プレイヤーがレーン外に出ていたら
		if (posX < -m_pPrimary->m_fLane)
		{
			// 中に戻す
			m_pPrimary->SetPosX(-m_pPrimary->m_fLane);
		}
	}
}

void CPlayer::PlayerNomarActivity::InputRight()
{
	if (m_bInRight)
	{
		m_pPrimary->AddPosX(m_pPrimary->m_fLane);	// 右に移動
		float posX = m_pPrimary->GetPosX();	// プレイヤーの位置取得
		// プレイヤーがレーン外に出ていたら
		if (posX > m_pPrimary->m_fLane)
		{
			// 中に戻す
			m_pPrimary->SetPosX(m_pPrimary->m_fLane);
		}
	}
}