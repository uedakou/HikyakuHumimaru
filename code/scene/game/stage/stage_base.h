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
			// �v���C���
			class Stage_Play_Strategy : public Stage_Strategy
			{
			public:
				Stage_Play_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Play_Strategy() {};
				virtual Stage_Strategy* update(nsPrev::CBase*& owner);
			};
			// �S�[�����
			class Stage_Goal_Strategy : public Stage_Strategy
			{
			public:
				enum class SelectGoal {
					StageSelect = 0,	// �X�e�[�W�Z���N�g
					ReTry,				// ���X�^�[�g
					MAX,
				};// �Z���N�g���
				Stage_Goal_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Goal_Strategy();
				virtual Stage_Strategy* update(nsPrev::CBase*& owner);
				int m_nSelect;
				int m_nSelectOld;
				CObject2D* m_pSelect[static_cast<int>(SelectGoal::MAX)];	// �Z���N�g
				CObject2D* m_pSelectBG;	// �Z���N�g
				CObject2D* m_GoalPopup;	// �|�b�v�A�b�v
				CObject2D* m_BG;	// �|�b�v�A�b�v
				static const D3DXVECTOR3 s_SelectPos;	// �Z���N�g�ʒu
				static const D3DXVECTOR3 s_SelectSiz;	// �Z���N�g�傫��
				static const D3DXVECTOR3 s_PopupPos;	// �Z���N�g�ʒu
				static const D3DXVECTOR3 s_PopupSiz;	// �Z���N�g�傫��

			};
			// ���S���
			class Stage_Death_Strategy : public Stage_Strategy
			{
			public:
				enum class SelectGoal {
					StageSelect = 0,	// �X�e�[�W�Z���N�g
					ReTry,				// ���X�^�[�g
					MAX,
				};// �Z���N�g���
				Stage_Death_Strategy(CStage_Base* pPrimary);
				virtual ~Stage_Death_Strategy();
				virtual Stage_Strategy* update(nsPrev::CBase*& owner);
				int m_nPLMotionCnt;
				int m_nSelect;
				int m_nSelectOld;
				CObject2D* m_pSelect[static_cast<int>(SelectGoal::MAX)];	// �Z���N�g
				CObject2D* m_pSelectBG;	// �Z���N�g
				CObject2D* m_GoalPopup;	// �|�b�v�A�b�v
				CObject2D* m_BG;	// �|�b�v�A�b�v
				static const int s_nPLMotionCnt;
				static const D3DXVECTOR3 s_SelectPos;	// �Z���N�g�ʒu
				static const D3DXVECTOR3 s_SelectSiz;	// �Z���N�g�傫��
				static const D3DXVECTOR3 s_PopupPos;	// �Z���N�g�ʒu
				static const D3DXVECTOR3 s_PopupSiz;	// �Z���N�g�傫��

			};
			Stage_Strategy* m_pStrategy;	// �X�V�X�g���e�W

			// �֐�
			void Load(const string& filePath);	// ���[�h

			// �����o�ϐ��ݒ�
			int m_nNumScroll;	// �X�N���[���擾��
			int m_nNumScrollOld;	// ���X�N���[���擾��
			bool m_bPose;	// �|�[�Y���
			bool m_bCameraFollowPlayer;	// �J�������v���C���[��Ǐ]���邩������
			float m_fCameraRot;		// �J�����̊p�x
			float m_fGool;	// ����
			CObject2D* m_pNumScroll[static_cast<int>(CGameData::Stage::MAX)];	// �X�N���[���擾���\��
		private:
			// �����o�ϐ��̏����l
			static const float s_fCameraRot;	// �����v���C���[����̃J�����̊p�x
			static const D3DXVECTOR3 NumScrollPos;	// �X�N���[���擾���\���ʒu(��Ԗ�)
			static const D3DXVECTOR3 NumScrollSiz;	// �X�N���[���擾���\���傫��
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
