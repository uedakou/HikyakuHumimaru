//============================================
//
// 障害物(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_tall.h"	// トールオブジェクト
#include "player.h"

CObstaclesToll::CObstaclesToll()
{
}

CObstaclesToll::~CObstaclesToll()
{
}

void CObstaclesToll::Init()
{
	CObstacles::Init();
}

void CObstaclesToll::Uninit()
{
	CObstacles::Update();
}

void CObstaclesToll::Update()
{
	CObstacles::Update();
}

void CObstaclesToll::Draw()
{
	CObstacles::Draw();
}

void CObstaclesToll::HitTest()
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
				break;
			}
			pObject[nCnt] = pNext;
		}
	}
}

CObstaclesToll* CObstaclesToll::clate(D3DXVECTOR3 pos)
{
	return nullptr;
}
