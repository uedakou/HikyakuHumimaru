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
			CBase(scene, gameData)
		{
			m_bPose = false;
			m_bCameraFollowPlayer = true;
			m_fCameraRot = s_fCameraRot;
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
#ifdef _DEBUG
			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
#endif // !_DEBUG
			return this;
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