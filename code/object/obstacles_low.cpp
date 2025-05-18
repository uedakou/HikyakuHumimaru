//============================================
//
// 障害物(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_low.h"// ロウオブジェクト
#include "player.h"

CObstaclesLow::CObstaclesLow()
{
}

CObstaclesLow::~CObstaclesLow()
{
}

void CObstaclesLow::Init()
{
	CObstacles::Init();
}

void CObstaclesLow::Uninit()
{
	CObstacles::Uninit();
}

void CObstaclesLow::Update()
{
	CObstacles::Update();
}

void CObstaclesLow::Draw()
{
	CObstacles::Draw();
}

void CObstaclesLow::HitTest()
{
	CObject* pObject[MAX_PRIORITY];
	CObject* pNext = nullptr;
	CObject::GetAllObject(pObject);
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		while (pObject[nCnt] != nullptr)
		{
			pNext = pObject[nCnt]->GetNext();
			CPlayer* player = dynamic_cast<CPlayer*>(pObject[nCnt]);
			if (player)
			{
				D3DXVECTOR3 PLpos = player->GetPos();
				D3DXVECTOR3 PLcol = player->GetCollisionSiz();
				D3DXVECTOR3 pos = GetPos();
				if (PLpos.z + PLcol.z * 0.5f > pos.z - s_Collision.z * 0.5f &&
					PLpos.z - PLcol.z * 0.5f < pos.z + s_Collision.z * 0.5f &&
					PLpos.x + PLcol.x * 0.5f > pos.x - s_Collision.x * 0.5f &&
					PLpos.x - PLcol.x * 0.5f < pos.x + s_Collision.x * 0.5f)
				{
					player->Hit(1);
				}
			}
			pObject[nCnt] = pNext;
		}
	}
}

CObstaclesLow* CObstaclesLow::clate(D3DXVECTOR3 pos)
{
	return nullptr;
}
