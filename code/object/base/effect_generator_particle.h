//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR_PAETICLE_H_
#define _EFFECT_GENERATOR_PAETICLE_H_
#include "effect_generator_base.h"	// �G�t�F�N�g�W�F�l���[�^�[

class CEffectGeneratorPaeticle : public CEffectGeneratorBase
{
public:
	CEffectGeneratorPaeticle();
	virtual ~CEffectGeneratorPaeticle();
	bool Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	// �������
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						// ����
	void SetLength(float fLength) { m_fLength = fLength; }				// ����
	void SetDiffusion(float fDiffusion) { m_fDiffusion = fDiffusion; }	// �g�U��(�p�x)
	void SetCole(D3DXCOLOR Cor) { m_pCor = Cor; }						// �F
	void SetTexture(const char* aFileName);
	void TimeController();

	static CEffectGeneratorPaeticle* create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan);	// ����(����,����, �g�U�p�x,�F,�p�[�e�B�N����������, �Ԋu)
	static CEffectGeneratorPaeticle* create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife);	// ����(����,����, �g�U�p�x,�F,�p�[�e�B�N����������, �Ԋu,�W�F�l���[�^�[��������)
private:
	// �������
	D3DXVECTOR3 m_rot;	// ����
	float m_fLength;	// �^����
	float m_fDiffusion;	// �g�U��(�p�x)
	D3DXCOLOR m_pCor;	// �F
	int m_nLifeParticle;			// �p�[�e�B�N���̃��C�t
	string m_aTexture;	// �e�N�X�`��
	// ���ԊǗ�
	int m_nCreatSpan;		// �����Ԋu
	int m_nCntCreatTime;	// ��������
};

#endif // !_EFFECT_GENERATOR__PAETICLE_H_