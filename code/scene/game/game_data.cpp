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
		}
		CGameData::~CGameData()
		{

		}
	}
}