//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
// �I�u�W�F�N�g�ۑ�
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