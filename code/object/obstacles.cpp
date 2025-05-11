//============================================
//
// プレイヤー[obstacles.cpp]
// Author:Uedakou
// 
//============================================
#include"obstacles.h"	// オブジェクト障害物
#include "player.h"		// プレイヤー
#include "base/character.h"	// キャラクター
/// <summary>
/// コンストラクタ
/// </summary>
CObstacles::CObstacles()
{
	m_type = TYPE::TALL;	// 種類を高壁にする高壁
	SetType(CObjectX::TYPE::OBSTACLES);	// 種類を障害物に設定
	m_pHitStrateg = new HitStrateg();
	
}
/// <summary>
/// デストラクタ
/// </summary>
CObstacles::~CObstacles()
{
}
/// <summary>
/// 初期化処理
/// </summary>
void CObstacles::Init()
{
	CObjectX::Init();
}
/// <summary>
/// 終了処理
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
/// 更新
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
/// 描画
/// </summary>
void CObstacles::Draw()
{
	CObjectX::Draw();
}
/// <summary>
/// 障害物生成
/// </summary>
/// <param name="type">障害物の種類</param>
/// <param name="pos">障害物の位置</param>
/// <returns>生成した障害物のポインター</returns>
CObstacles* CObstacles::clate(TYPE type, D3DXVECTOR3 pos)
{
	CObstacles* p = new CObstacles();
	p->SetPos(pos);	// 位置設定
	p->m_type = type;	// 種類設定
	int nID = 0;	// モデルID保存用
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
/// 背の高い障害物コンストラクタ
/// </summary>
/// <param name="pPrimary">親</param>
CObstacles::TallHitStrateg::TallHitStrateg()
{
}
/// <summary>
/// 背の高い障害物デストラクタ
/// </summary>
CObstacles::TallHitStrateg::~TallHitStrateg()
{
}
/// <summary>
/// 背の高い障害物ヒット処理
/// </summary>
void CObstacles::TallHitStrateg::update(CPlayer* pPlayer)
{

}
/// <summary>
/// 高い位置の障害物コンストラクタ
/// </summary>
/// <param name="pPrimary">親</param>
CObstacles::HighHitStrateg::HighHitStrateg()
{
}
/// <summary>
/// 高い位置の障害物デストラクタ
/// </summary>
CObstacles::HighHitStrateg::~HighHitStrateg()
{
}
/// <summary>
/// 高い位置の障害物ヒット処理
/// </summary>
void CObstacles::HighHitStrateg::update(CPlayer* pPlayer)
{

}
/// <summary>
/// 低い位置の障害物コンストラクタ
/// </summary>
/// <param name="pPrimary">親</param>
CObstacles::LowHitStrateg::LowHitStrateg()
{
}
/// <summary>
/// 低い位置の障害物デストラクタ
/// </summary>
CObstacles::LowHitStrateg::~LowHitStrateg()
{
}
/// <summary>
/// 低い位置の障害物ヒット処理
/// </summary>
void CObstacles::LowHitStrateg::update(CPlayer* pPlayer)
{

}
