//===========================================
// 
// ゲームステージ選択[scene_game_stageselect.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_stageselect.h"			// ステージセレクト
#include "../../object/base/object.h"		// オブジェクト
#include "../../object/base/object_3D.h"	// オブジェクト3d
#include "../../object/base/object_2D.h"	// オブジェクト2d
#include "../../base/input.h"				// 入力
#include "../../object/player.h"			// プレイヤー
#include "game_data.h"						//　ゲームデータ

namespace Scene {
	namespace Game {
		// 他クラス
		class CSceneDebug;				// デバッグ
		class CStage_000;				// ステージ000
		class CStage_001;				// ステージ001

		// 定数定義
		const int CScen_Game_StageSelect::s_nPressHoldLimit = 10;	// 入力開始カウント
		const D3DXVECTOR3 CScen_Game_StageSelect::s_SelectSiz = { 200.0f, 200.0f, 0.0f };	// 入力開始カウント
		const D3DXVECTOR3 CScen_Game_StageSelect::s_NotSelectSiz = { 100.0f, 100.0f, 0.0f };	// 入力開始カウント

		CScen_Game_StageSelect::CScen_Game_StageSelect(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();

			m_bPose = false;	// ポーズ状態
			m_nSetlect = 0;	// 現選択
			m_nCntPressHold = 0;	// 長押しカウント
			m_bNext = false;	// 次選択済みかどうか
			// ステージ選択のオブジェクト
			for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++ )
			{
				m_pStage[nCnt] = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f + 200.0f * nCnt, SCREEN_H * 0.5f, 0.0f), s_NotSelectSiz);
				switch (static_cast<Select>(nCnt))
				{
				case Select::STAGE_000:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_000.png");
					break;
				case Select::STAGE_001:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_001.png");
					break;
				case Select::STAGE_002:
					m_pStage[nCnt]->SetTexture("data/TEXTURE/StageSelect_002.png");
					break;
				default:
					break;
				}
			}
			// 一つ目のサイズを選択済みにする
			m_pStage[0]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));


			// 背景
			CObject2D* pBG = nullptr;
			pBG = CObject2D::creat(2, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0));	// 生成
			pBG->SetTexture("data/TEXTURE/Provisional/BG_000.png");	// テクスチャ

			pCamera->SetPosV(D3DXVECTOR3(0.0f, 100.0f, -400.0f));
			pCamera->SetRotX(1.3f);	// カメラ向き

			// プレイヤー設定
			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得
			pPlayer->SetNormalUpdate(false);	// 通常時更新設定
			pPlayer->SetPoseUpdate(false);	// 通常時更新設定
			pPlayer->SetNormalDraw(false);	// 通常時描画設定
			pPlayer->SetPoseDraw(false);		// ポーズ時描画設定
			pPlayer->SetMove(false);	// モーションの動きを設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
		}

		CScen_Game_StageSelect::~CScen_Game_StageSelect()
		{
		}

		nsPrev::CBase* CScen_Game_StageSelect::Update()
		{

			CManager* pManager = CManager::GetInstance();	// マネージャー
			CInputKeyboard* pInKey = pManager->GetInKey();	// キーボード入力

			if (pInKey->GetTrigger(DIK_P))
			{
				m_bPose = !m_bPose;
			}

			if (m_bPose == false)
			{


				int nSetlectOld = m_nSetlect;	// 旧位置を記憶
				// 左入力したら
				if (pInKey->GetTrigger(DIK_A) ||
					pInKey->GetTrigger(DIK_LEFT))
				{
					// 選択が決定されていなかったら
					if (m_bNext == false)
					{
						// 選択を一つ戻す
						m_nSetlect--;
						// 最小以下なら戻らないようにする
						if (m_nSetlect < 0)
						{
							m_nSetlect = 0;
						}
					}

				}
				// 左入力し続けたら
				//else if (pInKey->GetRepeat(DIK_A) ||
				//	pInKey->GetRepeat(DIK_LEFT))
				//{
				//	// 連続入力をカウントする
				//	m_nCntPressHold++;
				//	// c_nPressHoldLimit以上長押ししたら
				//	if (m_nCntPressHold >= c_nPressHoldLimit)
				//	{
				//		// 選択が決定されていなかったら
				//		if (m_bNext == false)
				//		{
				//			// 選択を一つ戻す
				//			m_nSetlect--;
				//			// 最小以下なら戻らないようにする
				//			if (m_nSetlect < 0)
				//			{
				//				m_nSetlect = 0;
				//			}
				//		}
				//	}

				//}
				// 右入力したら
				else if (pInKey->GetTrigger(DIK_D) ||
					pInKey->GetTrigger(DIK_RIGHT))
				{
					// 選択が決定されていなかったら
					if (m_bNext == false)
					{
						// 選択を一つ進める
						m_nSetlect++;
						// 最大以上なら先に進まないようにする
						if (m_nSetlect >= static_cast<int>(Select::MAX))
						{
							m_nSetlect = static_cast<int>(Select::MAX) - 1;
						}
					}
				}
				// 右入力し続けたら
				//else if (pInKey->GetRepeat(DIK_A) ||
				//	pInKey->GetRepeat(DIK_LEFT))
				//{
				//	// 連続入力をカウントする
				//	m_nCntPressHold++;
				//	// c_nPressHoldLimit以上長押ししたら
				//	if (m_nCntPressHold >= c_nPressHoldLimit)
				//	{
				//		// 選択が決定されていなかったら
				//		if (m_bNext == false)
				//		{
				//			// 選択を一つ進める
				//			m_nSetlect++;
				//			// 最大以上なら先に進まないようにする
				//			if (m_nSetlect >= static_cast<int>(Select::MAX))
				//			{
				//				m_nSetlect = static_cast<int>(Select::MAX) - 1;
				//			}
				//		}
				//	}
				//}
				// 移動を入力されていなかったら
				else
				{
					m_nCntPressHold = 0;
				}

				// 決定を入力したら
				if (pInKey->GetTrigger(DIK_RETURN) ||
					pInKey->GetTrigger(DIK_SPACE))
				{
					m_bNext = true;
				}

				//旧選択と現選択が違ったら
				if (m_nSetlect != nSetlectOld)
				{
					// 選択した物を大きくする
					m_pStage[m_nSetlect]->SetScl(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
					// 選択していた物を小さくする
					m_pStage[nSetlectOld]->SetScl(D3DXVECTOR3(1.0f, 1.0f, 0.0f
					));
					// 左に選択したら
					if (m_nSetlect < nSetlectOld)
					{
						// 左に移動させる
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(200.0f);
						}
					}
					// 右に選択したら
					else
					{
						// 右に移動させる
						for (int nCnt = 0; nCnt < static_cast<int>(Select::MAX); nCnt++)
						{
							m_pStage[nCnt]->AddPosX(-200.0f);
						}
					}

				}

				if (m_bNext == true)
				{// 選択を決定したら
					switch (static_cast<Select>(m_nSetlect))
					{
					case Select::STAGE_000:

						return makeScene<CStage_000>(m_gameData);
						break;
					case Select::STAGE_001:
						return makeScene<CStage_001>(m_gameData);
						break;
					case Select::STAGE_002:
						return makeScene<CSceneDebug>(m_gameData);
						break;
					default:
						break;
					}
				}
			}
			return this;
		}

		void CScen_Game_StageSelect::Draw() const
		{
		}

		bool CScen_Game_StageSelect::GetPose()
		{
			return m_bPose;
		}
		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CScen_Game_StageSelect>(CGameData* gamaData) {
			return new CScen_Game_StageSelect(this, gamaData);
		}
	}
}