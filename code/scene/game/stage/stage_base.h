//===========================================
// 
// チュートリアルステージ[stage_001.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_BASE_H_
#define _STAGE_BASE_H_
#include "../scene_game.h"	// シーンゲームベース
#include "./../../../base/pch.h"	// プリコンパイル

class CObject2D;
namespace Scene {
	namespace Game {
		class CStage_Base : public CBase
		{
		public:
			CStage_Base(CBase* game, CGameData* gameData);
			virtual ~CStage_Base();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		protected:
			// 更新描画
			class Stage_Strategy
			{
			public:
				Stage_Strategy(CStage_Base* pPrimary) : m_pPrimary(pPrimary) {}	// コンストラクタ
				virtual ~Stage_Strategy() { m_pPrimary = nullptr; };
				virtual Stage_Strategy* update(nsPrev::CBase*& owner) = 0;
				CStage_Base* m_pPrimary;	// 親
			};
			class Stage_Play_Strategy : public Stage_Strategy
			{
			public:
				Stage_Play_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Play_Strategy() {};
				virtual Stage_Strategy* update(nsPrev::CBase*& owner);
			};
			class Stage_Goal_Strategy : public Stage_Strategy
			{
			public:
				enum class SelectGoal {
					StageSelect = 0,	// ステージセレクト
					ReTry,				// リスタート
					MAX,
				};// セレクト種類
				Stage_Goal_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Goal_Strategy();
				virtual Stage_Strategy* update(nsPrev::CBase*& owner);
				int m_nSelect;
				int m_nSelectOld;
				CObject2D* m_pSelect[static_cast<int>(SelectGoal::MAX)];	// セレクト
				CObject2D* m_pSelectBG;	// セレクト
				CObject2D* m_GoalPopup;	// ポップアップ
				CObject2D* m_BG;	// ポップアップ
				static const D3DXVECTOR3 s_SelectPos;	// セレクト位置
				static const D3DXVECTOR3 s_SelectSiz;	// セレクト大きさ
				static const D3DXVECTOR3 s_PopupPos;	// セレクト位置
				static const D3DXVECTOR3 s_PopupSiz;	// セレクト大きさ

			};
			Stage_Strategy* m_pStrategy;	// 更新ストラテジ

			// 関数
			void Load(const string& filePath);	// ロード

			// メンバ変数設定
			int m_nScroll;	// スクロール
			bool m_bPose;	// ポーズ状態
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかそうか
			float m_fCameraRot;		// カメラの角度
			float m_fGool;	// 

		private:
			// メンバ変数の初期値
			static const float s_fCameraRot;	// 初期プレイヤーからのカメラの角度
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
