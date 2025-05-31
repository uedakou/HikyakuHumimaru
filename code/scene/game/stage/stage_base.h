//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_001.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_BASE_H_
#define _STAGE_BASE_H_
#include "../scene_game.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��

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
			// �֐�
			void Load(const string& filePath);	// ���[�h
			// �����o�ϐ��ݒ�
			bool m_bPose;	// �|�[�Y���
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩������
			float m_fCameraRot;		// �J�����̊p�x

		private:
			// �����o�ϐ��̏����l
			static const float s_fCameraRot;	// �����v���C���[����̃J�����̊p�x
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
