//===========================================
// 
// チュートリアルステージ[stage_tutorial.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_tutorial.h"		// チュートリアル

#include "../../../object/player.h"	// プレイヤー
#include "../../../object/base/object_2D.h"	// ポップアップ用2D
#include "../../../object/base/object_3D.h"	// ポップアップ用3D
#include "../../../object/base/object_fade.h"	// フェード
#include "../../../object/base/object_billboard.h"	// ビルボード
#include "../game_data.h"	// ゲームデータ


#define Enemy 1
#define Stage 1

namespace Scene {
	namespace Game {
		
		//============================================
		// コンスト
		//============================================
		CStage_Tutorial::CStage_Tutorial(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();

			m_nCntMakeFilde = 0;
#if Stage
			// フィールド
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);

			// ビルボード
			CObjectBillbord* pBillbord = nullptr;
			float fRand = 0;
			//for (int nCnt = 0; nCnt < 39; nCnt++)
			//{
			//	fRand = (float)(rand() % 100 / 10);
			//	pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			//	pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			//	pBillbord->SetType(CObjectBillbord::TYPE::TREE);

			//	fRand = (float)(rand() % 100 / 10);
			//	pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			//	pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			//	pBillbord->SetType(CObjectBillbord::TYPE::TREE);

			//}
#endif // Stage

			m_pUpdate = new CTutorial000(gameData);

			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			pCamera->SetRotX(1.3f);	// カメラ向き

			// プレイヤー設定
			pPlayer->SetNormalUpdate(false);	// 通常時更新設定
			pPlayer->SetNormalDraw(false);	// 通常時描画設定
			pPlayer->SetPoseDraw(false);		// ポーズ時描画設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
			pPlayer->SetMotionMove(false);	// モーションの動きを設定

			CFade::creat(CFade::TYPE::WHITE_IN, 30);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::~CStage_Tutorial()
		{
			// 更新を削除
			if (m_pUpdate != nullptr)
			{
				delete m_pUpdate;
			}

		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_Tutorial::Update()
		{
			CManager* manager = CManager::GetInstance();	// マネージャー
			bool b = manager->GetSceneManager()->GetPose();
			if (b == false)
			{

				CInputKeyboard* Key = manager->GetInKey();	// キーボード入力
#if Stage


				CObject* Top[MAX_PRIORITY];
				CObject::GetAllObject(Top);
				// 地面生成
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					CObject* pObject = Top[nCnt];
					CObject* pNext = nullptr;
					while (pObject != nullptr)
					{
						pNext = pObject->GetNext();

						pObject = pNext;
					}
				}
#endif // Stage

				// チュートリアル更新
				CTutorial* p = m_pUpdate->update();
				if (p != m_pUpdate)
				{
					delete m_pUpdate;
					m_pUpdate = p;
					if (p == nullptr)
					{
						//return makeScene<CStage_000>(m_gameData);
					}
				}


			}
			return this;
		}
		void CStage_Tutorial::Draw() const
		{
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_Tutorial::GetPose()
		{
			return false;
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_Tutorial>(CGameData* gamaData) {
			return new CStage_Tutorial(this, gamaData);
		}

		//============================================
		// チュートリアル
		//============================================
		//============================================
		// コンストラクタ
		//============================================
		CStage_Tutorial::CTutorial000::CTutorial000(CGameData* gamaData):
			CTutorial(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;
			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));

			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_000.png");
			m_bNext = false;
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial000::~CTutorial000()
		{
			if (m_pPopup != nullptr)
			{
				m_pPopup->DeathFlag();
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorial* CStage_Tutorial::CTutorial000::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();
			if (pKey->GetTrigger(DIK_W)||
				pKey->GetTrigger(DIK_A)||
				pKey->GetTrigger(DIK_S)||
				pKey->GetTrigger(DIK_D))
			{
				m_bNext = true;
			}
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					return new CTutorial001(m_gameData);
				}
			}
			return this;
		}
		//============================================
		// コンストラクト
		//============================================
		CStage_Tutorial::CTutorial001::CTutorial001(CGameData* gamaData):
			CTutorial(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;
			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));

			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_001.png");

			m_bNext = false;
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial001::~CTutorial001()
		{
			if (m_pPopup != nullptr)
			{
				m_pPopup->DeathFlag();
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorial* CStage_Tutorial::CTutorial001::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();
			if (pKey->GetTrigger(DIK_SPACE) )
			{
				m_bNext = true;
			}
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					return new CTutorial002(m_gameData);
				}
			}

			return this;
		}
		//============================================
		// コンストラク
		//============================================
		CStage_Tutorial::CTutorial002::CTutorial002(CGameData* gamaData):
			CTutorial(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;
			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));

			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_002.png");
			CObject* Top[MAX_PRIORITY];
			CObject::GetAllObject(Top);
			for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			{
				CObject* pObject = Top[nCnt];
				CObject* pNext = nullptr;
				while (pObject != nullptr)
				{
					pNext = pObject->GetNext();
					if (pObject->GetType() == CObject::TYPE::CHARACTER)
					{
						if (static_cast<CCharacter*>(pObject)->GetType() == CCharacter::TYPE::PLAYER)
						{
							D3DXVECTOR3 pos = static_cast<CPlayer*>(pObject)->GetPos();

			
							break;
						}
					}
					pObject = pNext;
				}
			}
			m_bNext = false;
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial002::~CTutorial002()
		{
			if (m_pPopup != nullptr)
			{
				m_pPopup->DeathFlag();
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorial* CStage_Tutorial::CTutorial002::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();

				m_bNext = true;
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					CFade::creat(CFade::TYPE::WHITE_OUT, 30);

					return nullptr;
				}
			}
			return this;
		}
		//============================================
		// デバッグ
		//============================================
		CStage_Tutorial::CTutorialDebug::CTutorialDebug(CGameData* gamaData):
			CTutorial(gamaData)
		{

		}
		CStage_Tutorial::CTutorialDebug::~CTutorialDebug()
		{
		}
		CStage_Tutorial::CTutorial* CStage_Tutorial::CTutorialDebug::update()
		{


			return this;
		}
}
}