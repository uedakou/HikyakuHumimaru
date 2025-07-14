//===========================================
// 
// ゲームシーンベース[scene_game.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_
#include "../scene_base.h"	// シーンベース
#include "game_data.h"	// ゲームデータ保存ヘッダ
#include <thread>	// マルチスレッドを立てるのに必要
namespace Scene {
	namespace Game {
		class CGameManager;
		namespace nsPrev = Scene;
		class CBase : public nsPrev::CBase
		{
		protected:
			CBase(nsPrev::CBase* scene, CGameData* const gameData) :
				nsPrev::CBase(*scene),
				m_gameData(gameData)
			{
				CObject::ReleaseScene();
			}	// シーンリリース}
			CBase(const CBase&) = default;

		public:
			virtual ~CBase() = default;
		protected:

			CGameData* const m_gameData;
		public:

			virtual  nsPrev::CBase* Update() override = 0;
			virtual void Draw() const override = 0;
			bool GetPose()override = 0;

			//実体生成用関数
			template<typename T>
			nsPrev::CBase* makeScene();
			// makeSceneをスレッド分けして終了したら
			// ゲームマネージャーに次のシーンのポインタを渡す
			// 
			// 
			// 
		};
	}
}
#endif // !_SCENE_GAME_H_