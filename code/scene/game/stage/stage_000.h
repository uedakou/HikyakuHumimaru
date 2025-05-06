//===========================================
// 
// チュートリアルステージ[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_
#include "../scene_game.h"
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_000 : public CBase
		{
		public:
			CStage_000(CBase* game, CGameData* gameData);
			virtual ~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private: // プライベート関数
			//CText* m_pText;
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかそうか
			float m_fCameraRot;		// カメラの角度
			float m_fTutorialRange;	// チュートリアルイベント発生の範囲(PLの移動量以上＆PLの移動量*2以下)

			bool m_bTutorial_000;
			bool m_bTutorial_001;
			bool m_bTutorial_002;

			static const bool s_bCameraFollowPlayer;
			static const float s_fCameraRot;	// カメラの角度
			static const float s_fGool;			// ゴール距離
			// チュートリアルイベント
			static const float s_fTutorial_000;
			static const float s_fTutorial_001;
			static const float s_fTutorial_002;
			static const bool s_bTutorial_000;
			static const bool s_bTutorial_001;
			static const bool s_bTutorial_002;

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
