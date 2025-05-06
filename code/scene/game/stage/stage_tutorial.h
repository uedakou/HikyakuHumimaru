//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_
#include "../scene_game.h"
class CObject2D;

namespace Scene {
	namespace Game {
		class CStage_Tutorial : public CBase
		{
		public:
			CStage_Tutorial(CBase* game, CGameData* gameData);
			virtual ~CStage_Tutorial();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// ���
			class CTutorial
			{
			public:
				CTutorial(CGameData* gameData) { m_gameData = gameData; }
				virtual ~CTutorial() {}
				virtual CTutorial*update () = 0;
			protected:
				CGameData* m_gameData;
			};
			// �`���[�g���A��
			class CTutorial000 : public CTutorial
			{
			public:
				CTutorial000(CGameData* gamaData);
				~CTutorial000();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				bool m_bNext;	// ���ɍs���邩
			};
			class CTutorial001 : public CTutorial
			{
			public:
				CTutorial001(CGameData* gamaData);
				~CTutorial001();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				bool m_bNext;	// ���ɍs���邩
			};
			class CTutorial002 : public CTutorial
			{
			public:
				CTutorial002(CGameData* gamaData);
				~CTutorial002();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				bool m_bNext;	// ���ɍs���邩
			};
			class CTutorialDebug : public CTutorial	// �f�o�b�O
			{
			public:
				CTutorialDebug(CGameData* gamaData);
				~CTutorialDebug();
				virtual CTutorial* update();
			private:
			};
		private:
			int m_nCntMakeFilde;
			CTutorial* m_pUpdate;
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
