//===========================================
// 
// ステージ000[stage_tutorial.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_000.h"		// チュートリアル

#include "../../../object/player.h"	// プレイヤー
#include "../../../object/base/object_2D.h"	// ポップアップ用2D
#include "../../../object/base/object_3D.h"	// ポップアップ用3D
#include "../../../object/base/object_X.h"	// ポップアップ用X
#include "../../../object/base/object_fade.h"	// フェード
#include "../../../object/base/object_billboard.h"	// ビルボード
#include "../game_data.h"	// ゲームデータ
#include "../../../object/base/text.h"	// テキスト

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CStage_000::s_bCameraFollowPlayer = true;	// カメラがプレイヤーを追従するかどうか
		const float CStage_000::s_fCameraRot = 2.6f;	// プレイヤーからのカメラの角度
		const float CStage_000::s_fGool = 20000.0f;	// ゴール距離

		// チュートリアル
		const float CStage_000::s_fTutorial_000 = 2000.0f;	// チュートリアルイベント
		const float CStage_000::s_fTutorial_001 = 4000.0f;		// チュートリアルイベント
		const float CStage_000::s_fTutorial_002 = 6000.0f;		// チュートリアルイベント
		const float CStage_000::s_fTutorial_003 = 6000.0f;		// チュートリアルイベント
		const bool CStage_000::s_bTutorial_000 = false;	// チュートリアルイベント
		const bool CStage_000::s_bTutorial_001 = false;		// チュートリアルイベント
		const bool CStage_000::s_bTutorial_002 = false;		// チュートリアルイベント
		const bool CStage_000::s_bTutorial_003 = false;		// チュートリアルイベント
		const D3DXVECTOR3 CStage_000::s_TutorialPopupPos = { 1000.0f, 300.0f, 0.0f };	// チュートリアルのポップアップの位置
		const D3DXVECTOR3 CStage_000::s_TutorialPopupSiz = { 300.0f, 200.0f, 0.0f };	// チュートリアルのポップアップの大きさ
		//============================================
		// コンスト
		//============================================
		CStage_000::CStage_000(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース

			// メンバ変数設定
			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// カメラがプレイヤーを追従するかどうか
			m_fCameraRot = s_fCameraRot;	// プレイヤーからのカメラの角度
			m_fTutorialRange = 0.0f;	// チュートリアルイベント発生の範囲初期化

			m_bTutorial_000 = s_bTutorial_000;	// チュートリアルイベントフラグ
			m_bTutorial_001 = s_bTutorial_001;	// チュートリアルイベントフラグ
			m_bTutorial_002 = s_bTutorial_002;	// チュートリアルイベントフラグ
			m_bTutorial_003 = s_bTutorial_003;	// チュートリアルイベントフラグ

			for (int nCnt = 0; nCnt < static_cast<int>(TUTORIAL::MAX); nCnt++)
			{
				m_pTutorealPopup[nCnt] = CObject2D::creat(D3DXVECTOR3(s_TutorialPopupPos), D3DXVECTOR3(s_TutorialPopupSiz));// 生成
				m_pTutorealPopup[nCnt]->SetPoseDraw(false);
				m_pTutorealPopup[nCnt]->SetNormalDraw(false);
				switch (static_cast<TUTORIAL>(nCnt))
				{
				case TUTORIAL::Tutorial_000:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_001:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_002:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				case TUTORIAL::Tutorial_003:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Provisional/Glass000.png");
					break;
				default:
					Beep(1000, 300);
					break;
				}
			}

			// プレイヤー設定
			CPlayer* pPlayer = m_gameData->GetPlayer();	// プレイヤー取得
			pPlayer->SetNormalUpdate(true);	// 通常時更新設定
			pPlayer->SetNormalDraw(true);	// 通常時描画設定
			pPlayer->SetPoseDraw(true);		// ポーズ時描画設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// モーション設定
			pPlayer->SetMotionMove(true);	// モーションの動きを設定

			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得
			pPlActiv->SetInUP(false);		// 上入力設定
			pPlActiv->SetInDown(false);		// 下入力設定
			pPlActiv->SetInLeft(false);		// 左入力設定
			pPlActiv->SetInRight(false);	// 右入力設定

			float fPLSpeed = pPlayer->GetSpeed();
			m_fTutorialRange = fPLSpeed + fPLSpeed * 0.9f;

			//pPlayer->SetMove(false);

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

			//CFade::creat(CFade::TYPE::WHITE_IN, 30);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_000::~CStage_000()
		{

		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_000::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// ストラテジー取得

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

			// チュートリアルイベント発動
			if (playerPos.z > s_fGool &&
				playerPos.z < s_fGool + 3.0f)
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			else if (playerPos.z > s_fTutorial_000 &&
				playerPos.z < s_fTutorial_000 + m_fTutorialRange)
			{
				if (m_bTutorial_000 == false)
				{
					pPlayer->SetMove(false);	// 動きを止める
					pPlayer->SetMotionMove(false);	// モーションの動きを設定
					pPlActiv->SetInLeft(true);		// 左入力設定
					pPlActiv->SetInRight(true);	// 右入力設定

					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(true);		// ポップアップを表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(true);	// ポップアップを表示

					m_bTutorial_000 = true;		// フラグを立てる
				}
			}
			else if (playerPos.z > s_fTutorial_001 &&
				playerPos.z < s_fTutorial_001 + m_fTutorialRange)
			{
				if (m_bTutorial_001 == false)
				{
					pPlayer->SetMove(false);	// 動きを止める
					pPlayer->SetMotionMove(false);	// モーションの動きを設定
					pPlActiv->SetInUP(true);		// 上入力設定
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(true);		// ポップアップを表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(true);	// ポップアップを表示
					m_bTutorial_001 = true;		// フラグを立てる
				}
			}
			else if (playerPos.z > s_fTutorial_002 &&
				playerPos.z < s_fTutorial_002 + m_fTutorialRange)
			{
				if (m_bTutorial_002 == false)
				{
					pPlayer->SetMove(false);	// 動きを止める
					pPlayer->SetMotionMove(false);	// モーションの動きを設定
					pPlActiv->SetInDown(true);		// 下入力設定
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(true);		// ポップアップを表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(true);	// ポップアップを表示
					m_bTutorial_002 = true;
				}
			}
			else if (playerPos.z > s_fTutorial_003 &&
				playerPos.z < s_fTutorial_003 + m_fTutorialRange)
			{
				if (m_bTutorial_003 == false)
				{
					pPlayer->SetMove(false);	// 動きを止める
					pPlayer->SetMotionMove(false);	// モーションの動きを設定
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(true);		// ポップアップを表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(true);	// ポップアップを表示
					m_bTutorial_003 = true;
				}
			}

			// チュートリアルイベント
			if (m_bTutorial_000)
			{
				// 左に入力したら
				if (pKey->GetTrigger(DIK_A) ||
					pKey->GetTrigger(DIK_LEFT))
				{
					pPlayer->SetMove(true);			// 動かす
					pPlayer->SetMotionMove(true);	// モーションの動きを設定
					pPlActiv->InputLeft();	// 左入力
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// ポップアップを非表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// ポップアップを非表示
					m_bTutorial_000 = false;		// フラグを降ろす
				}

				if(pKey->GetTrigger(DIK_D) ||
					pKey->GetTrigger(DIK_RIGHT))
				{
					pPlayer->SetMove(true);			// 動かす
					pPlayer->SetMotionMove(true);	// モーションの動きを設定
					pPlActiv->InputRight();	// 右入力
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// ポップアップを非表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// ポップアップを非表示
					m_bTutorial_000 = false;		// フラグを降ろす
				}
			}
			else if (m_bTutorial_001)
			{
				// 左に入力したら
				if (pKey->GetTrigger(DIK_W) ||
					pKey->GetTrigger(DIK_UP))
				{
					pPlayer->SetMove(true);			// 動かす
					pPlayer->SetMotionMove(true);	// モーションの動きを設定
					pPlActiv->InputUP();	// 上入力
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(false);		// ポップアップを非表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(false);	// ポップアップを非表示
					m_bTutorial_001 = false;		// フラグを降ろす
				}
			}
			else if (m_bTutorial_002)
			{
				// 右に入力したら
				if (pKey->GetTrigger(DIK_S) ||
					pKey->GetTrigger(DIK_DOWN))
				{
					pPlayer->SetMove(true);			// 動かす
					pPlayer->SetMotionMove(true);	// モーションの動きを設定
					pPlActiv->InputDown();	// 下入力
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(false);		// ポップアップを非表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(false);	// ポップアップを非表示
					m_bTutorial_002 = false;		// フラグを降ろす
				}
			}
			else if (m_bTutorial_003)
			{
				// 何か入力したら
				if (pKey->GetTrigger())
				{
					pPlayer->SetMove(true);			// 動かす
					pPlayer->SetMotionMove(true);	// モーションの動きを設定
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(false);		// ポップアップを非表示
					m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(false);	// ポップアップを非表示
					m_bTutorial_003= false;		// フラグを降ろす
				}
			}

			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			return this;
		}
		void CStage_000::Draw() const
		{
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_000::GetPose()
		{
			return false;
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_000>(CGameData* gamaData) {
			return new CStage_000(this, gamaData);
		}
	}
}