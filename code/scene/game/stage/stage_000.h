//===========================================
// 
// チュートリアルステージ[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_
#include "../scene_game.h"	// シーンゲームベース
#include "./../../../base/pch.h"	// プリコンパイル
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_000 : public CBase
		{
		public:
			// チュートリアルイベント
			enum class TUTORIAL {
				Tutorial_000 = 0,	// 左右避け
				Tutorial_001,		// 飛び越え
				Tutorial_002,		// 潜り抜け
				Tutorial_003,		// アイテム
				MAX,
			};
			CStage_000(CBase* game, CGameData* gameData);
			virtual ~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// メンバ変数設定
			bool m_bPose;	// ポーズ状態
			//CText* m_pText;
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかそうか
			float m_fCameraRot;		// カメラの角度
			float m_fTutorialRange;	// チュートリアルイベント発生の範囲(PLの移動量以上＆PLの移動量*2以下)
			// チュートリアル
			bool m_bTutorial_000;	// イベントフラグ
			bool m_bTutorial_001;	// イベントフラグ
			bool m_bTutorial_002;	// イベントフラグ
			bool m_bTutorial_003;	// イベントフラグ
			CObject2D* m_pTutorealPopup[static_cast<int>(TUTORIAL::MAX)];	// チュートリアルポップアップ

			// メンバ変数の初期値
			static const bool s_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかどうか
			static const float s_fCameraRot;	// プレイヤーからのカメラの角度
			static const float s_fGool;			// ゴール距離
			// チュートリアル
			static const float s_fTutorial_000;	// チュートリアルのイベント発生位置
			static const float s_fTutorial_001;	// チュートリアルのイベント発生位置
			static const float s_fTutorial_002;	// チュートリアルのイベント発生位置
			static const float s_fTutorial_003;	// チュートリアルのイベント発生位置
			static const bool s_bTutorial_000;	// チュートリアルのイベントフラグ
			static const bool s_bTutorial_001;	// チュートリアルのイベントフラグ
			static const bool s_bTutorial_002;	// チュートリアルのイベントフラグ
			static const bool s_bTutorial_003;	// チュートリアルのイベントフラグ
			static const D3DXVECTOR3 s_TutorialPopupPos;	// チュートリアルのポップアップの位置
			static const D3DXVECTOR3 s_TutorialPopupSiz;	// チュートリアルのポップアップの大きさ

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
