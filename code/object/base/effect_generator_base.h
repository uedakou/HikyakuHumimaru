//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_base.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR__BASE_H_
#define _EFFECT_GENERATOR__BASE_H_
#include "object.h"	// �I�u�W�F�N�g
class CEffectGeneratorBase : public CObject
{
public:
	CEffectGeneratorBase();
	~CEffectGeneratorBase();
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	// ����
	void SetLifeSpan(int nSpan) { m_nLife = nSpan; }
	int GetLifeSpan() { return m_nLife; }
	int GetCntTime() { return m_nCntLifeTime; }

private:
	// ���ԊǗ�
	int m_nLife;	// �G�t�F�N�g�̎���
	int m_nCntLifeTime;	// ���݂̌o�ߎ���
};
#endif // !_EFFECT_GENERATOR__BASE_H_