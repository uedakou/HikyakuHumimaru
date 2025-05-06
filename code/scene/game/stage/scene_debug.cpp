//===========================================
// 
// デバックシーン[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// デバックシーン
#include "../../../base/manager.h"		// マネージャー
#include "../game_data.h"		// ゲームデータ
#include "../../../object/base/object_3D.h"	// ３Dオブジェクト
#include "../../../object/base/text.h"	// ３Dオブジェクト


namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CSceneDebug::s_bCameraFollowPlayer = true;
		const float CSceneDebug::s_fCameraRot = 2.6f;
		//============================================
		// コンストラクタ
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース

		// プレイヤー設定
			CPlayer* pPlayer = m_gameData->GetPlayer();
			pPlayer->SetNormalDraw(true);
			pPlayer->SetPoseDraw(true);
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

			// テキスト生成
			m_pText = CText::creat();

			m_fCameraRot = s_fCameraRot;

			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// カメラがプレイヤーを追従するかどうか

			//CFade::creat(CFade::TYPE::WHITE_IN, 30);
		}
		//============================================
		// デストラクタ
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			//if (m_pField != nullptr)
			//{
			//	m_pField->DeathFlag();
			//}
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CSceneDebug::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();

			// カメラをプレイヤーに追従させるなら
			if (m_bCameraFollowPlayer == true)
			{
				// プレイヤーが有るなら
				if (pPlayer != nullptr)
				{
#if _DEBUG
					if (pKey->GetTrigger(DIK_UP))
					{
						m_fCameraRot += 0.1f;
					}
					else if (pKey->GetTrigger(DIK_DOWN))
					{
						m_fCameraRot -= 0.1f;
					}
#endif // _DEBUG
					// カメラをプレイヤーに追従させる
					D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
					pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_fCameraRot) * 300.0f, playerPos.z + cosf(m_fCameraRot) * 300.0f));	// カメラに適応

					// カメラのプレイヤーからの向き
					//char text[MAX_TXT];
					//sprintf_s(text, sizeof(text), "CameraRot:%f\n", m_fCameraRot);

					//m_pText->SetText(text);
				}
			}

			// プレイヤーがループするようにする
			// プレイヤーがnullでなければ
			if (pPlayer != nullptr)
			{
				float posz = pPlayer->GetPosZ();
				if (posz >= 4000.0f)
				{
					pPlayer->SetPosZ(-5000.0f);
				}
			}

			if (pKey->GetTrigger(DIK_L))
			{
				return makeScene<CScen_Game_StageSelect>(m_gameData);
			}
			return this;
		}
		//============================================
		// 描画
		//============================================
		void CSceneDebug::Draw() const
		{
		}

		//============================================
		// ポーズ中取得
		//============================================
		bool CSceneDebug::GetPose()
		{
			return false;
		}

		template<>
		nsPrev::CBase* CBase::makeScene<CSceneDebug>(CGameData* gamaData) {
			return new CSceneDebug(this, gamaData);
		}
	}
}