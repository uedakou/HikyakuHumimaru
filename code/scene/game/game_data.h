//===========================================
// 
// ゲームデータ保持[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#include "../../object/player.h"			// プレイヤー

class CPlayer;
namespace Scene {
	namespace Game {
		class CGameData
		{
		public:
			CGameData();
			virtual ~CGameData();
			// 設定
			void SetPlayer(CPlayer* player) { m_player = player; }	// プレイヤー設定
			// 取得
			CPlayer* GetPlayer() { return m_player; }	// プレイヤー取得
		private:
			CPlayer* m_player;	// プレイヤー


		};
	}
}



#endif //_GAME_DATA_H_