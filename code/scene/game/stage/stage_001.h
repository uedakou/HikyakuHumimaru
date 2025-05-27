//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_001.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_H_
#define _STAGE_000_H_
#include "../scene_game.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_001 : public CBase
		{
		public:
			CStage_001(CBase* game, CGameData* gameData);
			virtual ~CStage_001();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// �֐�
			void Load();	// ���[�h
			void LoadT();	// ���[�h��

			// �����o�ϐ��ݒ�
			bool m_bPose;	// �|�[�Y���
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩������
			float m_fCameraRot;		// �J�����̊p�x

			// �����o�ϐ��̏����l
			static const bool s_bCameraFollowPlayer;	// �����J�������v���C���[��Ǐ]���邩�ǂ���
			static const float s_fCameraRot;	// �����v���C���[����̃J�����̊p�x
			static const float s_fGool;			// �S�[������
			static const string s_aStage;		// �X�e�[�W�p�X

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
