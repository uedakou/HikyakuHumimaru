//============================================
//
// プレイヤー[obstacles.cpp]
// Author:Uedakou
// 
//============================================
#include"obstacles.h"	// オブジェクト障害物

/// <summary>
/// コンストラクタ
/// </summary>
CObstacles::CObstacles()
{
	m_type = TYPE::TALL;	// 種類を高壁にする高壁
	SetType(CObjectX::TYPE::OBSTACLES);	// 種類を障害物に設定
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
}
/// <summary>
/// 更新
/// </summary>
void CObstacles::Update()
{
	CObjectX::Update();
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
