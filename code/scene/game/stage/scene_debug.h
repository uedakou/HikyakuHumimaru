//===========================================
// 
// �f�o�b�N�V�[��[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_DEBUG_H_
#include "../scene_game.h"	// �x�[�X�V�[��

class CObject3D;	// �I�u�W�F�N�g�R�c
class CText;	// �e�L�X�g

namespace Scene {
	namespace Game {
		class CSceneDebug : public CBase
		{
		public:
			CSceneDebug(CBase* scene, CGameData* gameData);
			virtual ~CSceneDebug()		override;
			virtual nsPrev::CBase* Update()	override;	// �X�V
			virtual void Draw() const override;	// �`��
			virtual bool GetPose()override;
		private:
			CText* m_pText;		// �e�L�X�g
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩�ǂ���
			float m_fCameraRot;		// �v���C���[����̃J�����̊p�x

			static const bool s_bCameraFollowPlayer;
			static const float s_fCameraRot;
		};
	}
}



#endif // !_SCENE_DEBUG_H_
