//===========================================
// 
// ゲームデータ保持[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
// オブジェクト保存
namespace Scene
{
	namespace Game
	{
		CGameData::CGameData()
		{
			m_player = nullptr;
			for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
			{
				m_nScore[nCnt] = 0;
			}

		}
		CGameData::~CGameData()
		{

		}
	}
}