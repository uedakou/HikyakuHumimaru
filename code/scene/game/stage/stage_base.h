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

class CObject2D;
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
			// �X�V�`��
			class Stage_Strategy
			{
			public:
				Stage_Strategy(CStage_Base* pPrimary) : m_pPrimary(pPrimary) {}	// �R���X�g���N�^
				virtual ~Stage_Strategy() { m_pPrimary = nullptr; };
				virtual Stage_Strategy* update(nsPrev::CBase*& owner) = 0;
				CStage_Base* m_pPrimary;	// �e
			};
			class Stage_Play_Strategy : public Stage_Strategy
			{
			public:
				Stage_Play_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Play_Strategy() {};
				virtual Stage_Play_Strategy* update(nsPrev::CBase*& owner);
			};
			class Stage_Goal_Strategy : public Stage_Strategy
			{
			public:
				virtual Stage_Goal_Strategy* update(nsPrev::CBase*& owner);
				enum class SelectGoal {
					StageSelect = 0,	// �X�e�[�W�Z���N�g
					ReTry,				// ���X�^�[�g
					MAX,
				};// �Z���N�g���
				Stage_Goal_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Goal_Strategy();

				SelectGoal m_Select;
				SelectGoal m_SelectOld;
				CObject2D* m_pSelect[static_cast<int>(SelectGoal::MAX)];	// �Z���N�g
				CObject2D* m_GoalPopup;	// �|�b�v�A�b�v
				static const D3DXVECTOR3 s_SelectSiz;
			};
			Stage_Strategy* m_pStrategy;	// �X�V�X�g���e�W

			// �֐�
			void Load(const string& filePath);	// ���[�h

			// �����o�ϐ��ݒ�
			bool m_bPose;	// �|�[�Y���
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩������
			float m_fCameraRot;		// �J�����̊p�x
			float m_fGool;	// 

		private:
			// �����o�ϐ��̏����l
			static const float s_fCameraRot;	// �����v���C���[����̃J�����̊p�x
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
