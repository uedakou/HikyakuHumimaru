//===========================================
// 
// ステージ000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_001.h"		// チュートリアル

#include "../../../object/player.h"	// プレイヤー
#include "../../../object/base/object_2D.h"	// ポップアップ用2D
#include "../../../object/base/object_3D.h"	// ポップアップ用3D
#include "../../../object/base/object_X.h"	// ポップアップ用X
#include "../../../object/base/object_fade.h"	// フェード
#include "../../../object/base/object_billboard.h"	// ビルボード
#include "../game_data.h"	// ゲームデータ
#include "../../../object/base/text.h"	// テキスト
#include "../../../object/obstacles_tall.h"	// 障害物
#include "../../../object/obstacles_high.h"	// 障害物
#include "../../../object/obstacles_low.h"	// 障害物
namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CStage_001::s_bCameraFollowPlayer = true;	// カメラがプレイヤーを追従するかどうか
		const float CStage_001::s_fCameraRot = 2.6f;	// プレイヤーからのカメラの角度
		const float CStage_001::s_fGool = 20000.0f;	// ゴール距離

		//============================================
		// コンスト
		//============================================
		CStage_001::CStage_001(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース
			CPlayer* pPlayer = m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			// メンバ変数設定
			m_bPose = false;
			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// カメラがプレイヤーを追従するかどうか
			m_fCameraRot = s_fCameraRot;	// プレイヤーからのカメラの角度

			// プレイヤー設定
			pPlayer->SetNormalUpdate(true);	// 通常時更新設定
			pPlayer->SetNormalDraw(true);	// 通常時描画設定
			pPlayer->SetPoseDraw(true);		// ポーズ時描画設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// モーション設定
			pPlayer->SetMotionMove(true);	// モーションの動きを設定
			pPlayer->SetMove(true);	// 動きを設定
			pPlayer->SetLife(1);	// 体力設定

			pPlActiv->SetInUP(false);		// 上入力設定
			pPlActiv->SetInDown(false);		// 下入力設定
			pPlActiv->SetInLeft(false);		// 左入力設定
			pPlActiv->SetInRight(false);	// 右入力設定

			// ワールド生成
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetTexture("data/TEXTURE/Provisional/Glass000.png");

			// カメラ向き
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_001::~CStage_001()
		{
			CPlayer* pPlayer = m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			pPlActiv->SetInUP(true);		// 上入力設定
			pPlActiv->SetInDown(true);		// 下入力設定
			pPlActiv->SetInLeft(true);		// 左入力設定
			pPlActiv->SetInRight(true);	// 右入力設定
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_001::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// ストラテジー取得

			// ポーズ入力
			if (pKey->GetTrigger(DIK_P))
			{
				m_bPose = !m_bPose;
				// ポーズしたら
				if (m_bPose)
				{
					// プレイヤーの動きを止める
					pPlayer->SetMove(false);
				}
				// ポーズを解除したら
				else
				{
					// プレイヤーの動かす
					pPlayer->SetMove(true);
				}
			}
			if (m_bPose == false)
			{
				// カメラをプレイヤーに追従させるなら
				if (m_bCameraFollowPlayer == true)
				{
					// プレイヤーが有るなら
					if (pPlayer != nullptr)
					{
						// カメラをプレイヤーに追従させる
						pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_fCameraRot) * 300.0f, playerPos.z + cosf(m_fCameraRot) * 300.0f));	// カメラに適応
					}
				}
			}
#ifdef _DEBUG
			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#endif // !_DEBUG
			return this;
		}
		void CStage_001::Draw() const
		{
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_001::GetPose()
		{
			return m_bPose;
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_001>(CGameData* gamaData) {
			return new CStage_001(this, gamaData);
		}
	}
}