//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_base.cpp]
// Author:Uedakou
// 
//============================================
#include "effect_generator_base.h"	// �G�t�F�N�g�W�F�l���[�^�[
//============================================
// �R���X�g
//============================================
CEffectGeneratorBase::CEffectGeneratorBase()
{
	m_nLife = -1;
	m_nCntLifeTime = 0;
	SetNormalDraw(false);	// �ʏ�`������Ȃ�
	SetPoseDraw(false);		// �|�[�Y���`�悵�Ȃ�

}
//============================================
// �f�X�g��
//============================================
CEffectGeneratorBase::~CEffectGeneratorBase()
{
}
//============================================
// ������
//============================================
void CEffectGeneratorBase::Init()
{
}
//============================================
// �I��
//============================================
void CEffectGeneratorBase::Uninit()
{
}
//============================================
// �X�V
//============================================
void CEffectGeneratorBase::Update()
{
	m_nCntLifeTime++;
	if (m_nLife != -1 &&
		m_nCntLifeTime >= m_nLife)
	{
		DeathFlag();
	}
}
//============================================
// �`��
//============================================
void CEffectGeneratorBase::Draw()
{
}