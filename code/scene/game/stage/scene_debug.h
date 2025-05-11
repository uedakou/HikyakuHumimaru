//===========================================
// 
// デバックシーン[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_DEBUG_H_
#include "../scene_game.h"	// ベースシーン

class CObject3D;	// オブジェクト３Ｄ
class CText;	// テキスト

namespace Scene {
	namespace Game {
		class CSceneDebug : public CBase
		{
		public:
			CSceneDebug(CBase* scene, CGameData* gameData);
			virtual ~CSceneDebug()		override;
			virtual nsPrev::CBase* Update()	override;	// 更新
			virtual void Draw() const override;	// 描画
			virtual bool GetPose()override;
		private:
			CText* m_pText;		// テキスト
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかどうか
			float m_fCameraRot;		// プレイヤーからのカメラの角度

			static const bool s_bCameraFollowPlayer;
			static const float s_fCameraRot;
		};
	}
}



#endif // !_SCENE_DEBUG_H_
