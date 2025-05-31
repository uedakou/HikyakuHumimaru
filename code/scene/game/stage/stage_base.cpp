//===========================================
// 
// ステージ000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_base.h"		// ステージ

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

#include <fstream>	// ファイルの読み込みに必要
#include <iostream>	// ファイルの読み込みに必要

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_Base::s_fCameraRot = 2.6f;	// 初期プレイヤーからのカメラの角度
		//============================================
		// コンスト
		//============================================
		CStage_Base::CStage_Base(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData),
			m_bPose(false) , m_bCameraFollowPlayer(true) , m_fGool(0)
		{
			m_fCameraRot = s_fCameraRot;
			m_pStrategy = new Stage_Play_Strategy(this);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Base::~CStage_Base()
		{
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_Base::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
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
			nsPrev::CBase* result = this;

			if (m_pStrategy != nullptr)
			{
				auto p = m_pStrategy->update(result);
				if (p != m_pStrategy)
				{
					delete m_pStrategy;
					m_pStrategy = p;
				}
			}

#ifdef _DEBUG
			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#endif // !_DEBUG
			return result;
		}
		void CStage_Base::Draw() const
		{
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_Base::GetPose()
		{
			return m_bPose;
		}
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pPrimary">親</param>
		CStage_Base::Stage_Play_Strategy::Stage_Play_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
		}
		/// <summary>
		/// 通常更新ストラテジ
		/// </summary>
		/// <returns></returns>
		CStage_Base::Stage_Play_Strategy* CStage_Base::Stage_Play_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// ストラテジー取得
			// ポーズ入力
			if (pKey->GetTrigger(DIK_P))
			{
				m_pPrimary->m_bPose = !(m_pPrimary->m_bPose);
				// ポーズしたら
				if (m_pPrimary->m_bPose)
				{
					// プレイヤーの動きを止める
					pPlayer->SetMove(false);
				}
				// ポーズを解除したら
				else
				{
					// プレイヤーを動かす
					pPlayer->SetMove(true);
				}
			}
			if (m_pPrimary->m_bPose == false)
			{
				// チュートリアルイベント発動
				if (playerPos.z > m_pPrimary->m_fGool)
				{
					owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
				}
			}
			// プレイヤーの体力が０以下なら
			if (pPlayer->GetLife() <= 0)
			{
				owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
			}
#ifdef _DEBUG
			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
			}
#endif // !_DEBUG

			return this;
		}


		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_SelectSiz {200.0f, 200.0f, 0.0f};
		/// <summary>
		/// ゴール時コンスト
		/// </summary>
		/// <param name="pPrimary">親</param>
		CStage_Base::Stage_Goal_Strategy::Stage_Goal_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				m_pSelect[nCnt] = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f + s_SelectSiz.x * nCnt, SCREEN_H * 0.5f, 0.0f), s_SelectSiz);
				switch (static_cast<SelectGoal>(nCnt))
				{
				case SelectGoal::StageSelect:	// ステージセレクトに戻る
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Provisional/End_000.png");
					break;
				case SelectGoal::ReTry:	// リトライ
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Provisional/End_000.png");
					break;
				default:
					break;
				}
			}
			m_GoalPopup = CObject2D::creat(D3DXVECTOR3(), D3DXVECTOR3());
			m_GoalPopup->SetTexture("data/TEXTURE/Provisional/End_000.png");
		}
		CStage_Base::Stage_Goal_Strategy::~Stage_Goal_Strategy()
		{
		}
		CStage_Base::Stage_Goal_Strategy* CStage_Base::Stage_Goal_Strategy::update(nsPrev::CBase*& owner)
		{

			
			if (m_Select != m_SelectOld)
			{
				m_pSelect[static_cast<int>(m_Select)]->SetColor(D3DXCOLOR(D3DCOLOR_RGBA(255, 255, 255, 255)));
				m_pSelect[static_cast<int>(m_SelectOld)]->SetColor(D3DXCOLOR(D3DCOLOR_RGBA(255, 255, 255, 255)));
			}
				return this;
		}
		/// <summary>
		/// ステージ読み込み
		/// </summary>
		void CStage_Base::Load(const string& filePath)
		{
			ifstream file(filePath.c_str());  // 読み込むファイルのパスを指定
			if (file.fail()) {
				MessageBoxA(nullptr, "開けませんでした", "エラー", MB_OK);
			}
			string str0, str1, str2, str3;	// 文字列格納用
			string _;	// スキップ用格納
			string aModelFile[MAX_MOTION_MODEL];	// モデルファイル

		// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
			while (file >> str0)
			{
				// コメントアウト
				if (str0[0] == '#')
				{
					getline(file, _);	// 一行スキップ
				}
				// 障害物TALL
				else if (str0.compare("OBSTACLES") == 0)
				{
					int nType = 0;	// 種類
					D3DXVECTOR3 pos = {};	// 位置
					D3DXVECTOR3 rot = {};	// 向き


					while (file >> str1 &&
						str1.compare("END_OBSTACLES") != 0)
					{
						// コメントアウト
						if (str1[0] == '#')
						{
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							nType = atoi(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							pos.x = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.y = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.z = stof(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル名を取得
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// 一行スキップ
						}
					}
					// 障害物生成
					switch (nType)
					{
					case 0:
						CObstaclesToll::clate(pos, rot);
						break;
					case 1:
						CObstaclesHigh::clate(pos, rot);
						break;
					case 2:
						CObstaclesLow::clate(pos, rot);
						break;
					default:
#ifdef _DEBUG
						OutputDebugStringA("デバッグ出力：存在しない障害物を生成しようとしました。\n");
						Beep(1200, 300);
#endif // _DEBUG
						break;
					}

				}
				else if (str0.compare("OBJECT") == 0)
				{
					int nType = 0;	// 種類
					D3DXVECTOR3 pos = {};	// 位置
					D3DXVECTOR3 rot = {};	// 向き
					CObjectX* pObject = nullptr;	// オブジェクト

					while (file >> str1 &&
						str1.compare("END_OBJECT") != 0)
					{
						// コメントアウト
						if (str1[0] == '#')
						{
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							nType = atoi(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							pos.x = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.y = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.z = stof(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル名を取得
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// 一行スキップ
						}
					}	/* !while (file >> str1 &&
					str1.compare("END_OBSTACLES") != 0)*/
					// 種類別生成
					if (nType == 0)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_000.x");
					}
					else if (nType == 1)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_001.x");
					}
					else
					{
						OutputDebugStringA("デバッグ出力：存在しないオブジェクトを生成しようとしました。\n");
						Beep(1200, 300);
					}
					if (pObject != nullptr)
					{
						pObject->SetPos(pos);
						pObject->SetRot(rot);
					}

				}
			}
			// ファイルを閉じる
			file.close();
		}

	}
}