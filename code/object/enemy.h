//============================================
//
// �G[enemy.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../object/base/character.h"

class CEnemy : public CCharacter
{
public:
	typedef enum {
		Enemy000 = 0,
		Enemy100,
		MAX,
	}ENEMY_TYPE;


	CEnemy();
	virtual ~CEnemy()		override;
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	virtual int GetNextMotion() override { return 0; }	// �����[�V����
	virtual void Hit(int nCntInvincible, int nDamage);	// �q�b�g
	ENEMY_TYPE GetType() { return m_type; }
protected:
	void SetSearch(bool bSearch) { m_bSearch = bSearch; }	// �����ς݂���ݒ�
	void SetTarget(CObject* pTarget) { m_pTarget = pTarget; }// �^�[�Q�b�g��ݒ�
	void SetType(ENEMY_TYPE type) { m_type = type; }

	CObject* GetTarget() { return m_pTarget; }	// �^�[�Q�b�g���擾

private:
	bool m_bSearch;	// �����ς݂�
	CObject* m_pTarget;

	ENEMY_TYPE m_type;

};







#endif // _ENEMY_H_