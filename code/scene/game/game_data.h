//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#include "../../object/player.h"			// �v���C���[

class CPlayer;
namespace Scene {
	namespace Game {
		class CGameData
		{
		public:
			CGameData();
			virtual ~CGameData();
			// �ݒ�
			void SetPlayer(CPlayer* player) { m_player = player; }	// �v���C���[�ݒ�
			// �擾
			CPlayer* GetPlayer() { return m_player; }	// �v���C���[�擾
		private:
			CPlayer* m_player;	// �v���C���[


		};
	}
}



#endif //_GAME_DATA_H_