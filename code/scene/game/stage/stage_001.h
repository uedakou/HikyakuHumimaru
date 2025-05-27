//===========================================
// 
// チュートリアルステージ[stage_001.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_H_
#define _STAGE_000_H_
#include "../scene_game.h"	// シーンゲームベース
#include "./../../../base/pch.h"	// プリコンパイル
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_001 : public CBase
		{
		public:
			CStage_001(CBase* game, CGameData* gameData);
			virtual ~CStage_001();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// 関数
			void Load();	// ロード
			void LoadT();	// ロード仮

			// メンバ変数設定
			bool m_bPose;	// ポーズ状態
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかそうか
			float m_fCameraRot;		// カメラの角度

			// メンバ変数の初期値
			static const bool s_bCameraFollowPlayer;	// 初期カメラがプレイヤーを追従するかどうか
			static const float s_fCameraRot;	// 初期プレイヤーからのカメラの角度
			static const float s_fGool;			// ゴール距離
			static const string s_aStage;		// ステージパス

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
