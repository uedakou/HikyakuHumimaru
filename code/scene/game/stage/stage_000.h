//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_
#include "../scene_game.h"	// �V�[���Q�[���x�[�X
#include "./../../../base/pch.h"	// �v���R���p�C��
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_000 : public CBase
		{
		public:
			// �`���[�g���A���C�x���g
			enum class TUTORIAL {
				Tutorial_000 = 0,	// ���E����
				Tutorial_001,		// ��щz��
				Tutorial_002,		// ���蔲��
				Tutorial_003,		// �A�C�e��
				MAX,
			};
			CStage_000(CBase* game, CGameData* gameData);
			virtual ~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// �����o�ϐ��ݒ�
			bool m_bPose;	// �|�[�Y���
			//CText* m_pText;
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩������
			float m_fCameraRot;		// �J�����̊p�x
			float m_fTutorialRange;	// �`���[�g���A���C�x���g�����͈̔�(PL�̈ړ��ʈȏさPL�̈ړ���*2�ȉ�)
			// �`���[�g���A��
			bool m_bTutorial_000;	// �C�x���g�t���O
			bool m_bTutorial_001;	// �C�x���g�t���O
			bool m_bTutorial_002;	// �C�x���g�t���O
			bool m_bTutorial_003;	// �C�x���g�t���O
			CObject2D* m_pTutorealPopup[static_cast<int>(TUTORIAL::MAX)];	// �`���[�g���A���|�b�v�A�b�v

			// �����o�ϐ��̏����l
			static const bool s_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩�ǂ���
			static const float s_fCameraRot;	// �v���C���[����̃J�����̊p�x
			static const float s_fGool;			// �S�[������
			// �`���[�g���A��
			static const float s_fTutorial_000;	// �`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_001;	// �`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_002;	// �`���[�g���A���̃C�x���g�����ʒu
			static const float s_fTutorial_003;	// �`���[�g���A���̃C�x���g�����ʒu
			static const bool s_bTutorial_000;	// �`���[�g���A���̃C�x���g�t���O
			static const bool s_bTutorial_001;	// �`���[�g���A���̃C�x���g�t���O
			static const bool s_bTutorial_002;	// �`���[�g���A���̃C�x���g�t���O
			static const bool s_bTutorial_003;	// �`���[�g���A���̃C�x���g�t���O
			static const D3DXVECTOR3 s_TutorialPopupPos;	// �`���[�g���A���̃|�b�v�A�b�v�̈ʒu
			static const D3DXVECTOR3 s_TutorialPopupSiz;	// �`���[�g���A���̃|�b�v�A�b�v�̑傫��

		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
