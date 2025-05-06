//============================================
//
// �G�t�F�N�g�W�F�l���[�^�[[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_generator_particle.h"	// �G�t�F�N�g�p�[�e�B�N���W�F�l���[�^�[
#include "effect_particle.h"	// �G�t�F�N�g�p�[�e�B�N��

//============================================
// �R���X�g
//============================================
CEffectGeneratorPaeticle::CEffectGeneratorPaeticle()
{
	// �������
	m_rot = { 0.0f, 0.0f, 0.0f };			// ����
	m_fLength = 0.0f;						// ����
	m_fDiffusion = 0.0f;					// �g�U��(�p�x)
	m_pCor = { 0.0f, 0.0f, 0.0f, 0.0f };	// �F
	m_aTexture = "data/TEXTURE/shadow000.jpg";					// �e�N�X�`��
	m_nLifeParticle = 0;					// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	m_nCreatSpan = 0;		// �����Ԋu
	m_nCntCreatTime = 0;	// ��������
}
//============================================
// �R���X�g
//============================================
CEffectGeneratorPaeticle::~CEffectGeneratorPaeticle()
{
}
//============================================
// ������
//============================================
void CEffectGeneratorPaeticle::Init()
{
	CEffectGeneratorBase::Init();
}
//============================================
// �I��
//============================================
void CEffectGeneratorPaeticle::Uninit()
{
	CEffectGeneratorBase::Uninit();
}
//============================================
// �X�V
//============================================
void CEffectGeneratorPaeticle::Update()
{
	if (IsDeathFlag() != true)
	{
		CEffectGeneratorBase::Update();
		m_nCntCreatTime--;
		if (m_nCntCreatTime <= 0)
		{
			m_nCntCreatTime = m_nCreatSpan;
			// +-����
			float B = 1000.0f;
			D3DXVECTOR3 RandRotA = {};
			RandRotA.x = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA.y = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA.z = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA /= (float)B;
			RandRotA += m_rot;
			D3DXVec3Normalize(&RandRotA, &RandRotA);

			D3DXVECTOR3 move = RandRotA * m_fLength;
			CEffectParticle::creat(GetPos(), move, m_pCor, m_aTexture, m_nLifeParticle);
		}
	}
}
//============================================
// �`��
//============================================
void CEffectGeneratorPaeticle::Draw()
{}
//============================================
// �e�N�X�`���ݒ�
//============================================
void CEffectGeneratorPaeticle::SetTexture(const char* aFileName)
{
	if (IsDeathFlag() != true)
	{
		m_aTexture = aFileName;
	}
}
//============================================
// ���ԊǗ�
//============================================
void CEffectGeneratorPaeticle::TimeController()
{
	//DWORD dwCuppentTime = 0;	// ���ݎ���
	//DWORD dwExecLastTime = 0;
	//bool bDeath = false;
	//while (bDeath == false)
	//{
	//	dwCuppentTime = timeGetTime();	// ���ݎ������擾
	//	if ((dwCuppentTime - dwExecLastTime) >= m_nCreatSpan)
	//	{


	//		dwExecLastTime = dwCuppentTime;
	//	}
	//}
}
//============================================
// ����
//============================================
CEffectGeneratorPaeticle* CEffectGeneratorPaeticle::creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan)
{
	CEffectGeneratorPaeticle* p = new CEffectGeneratorPaeticle();

	p->Init();

	// �������
	D3DXVec3Normalize(&(p->m_rot),&rot);	// ����
	p->m_fLength = fLength;			// ����
	p->m_fDiffusion = AngleToRadian(Diffusion);	// �g�U��(�p�x)
	p->m_pCor = Cor;				// �F
	p->m_nLifeParticle = nParticleLife;		// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	p->m_nCreatSpan = nCreatSpan;	// �����Ԋu

	return p;
}
CEffectGeneratorPaeticle* CEffectGeneratorPaeticle::creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife)
{
	CEffectGeneratorPaeticle* p = new CEffectGeneratorPaeticle();

	p->Init();

	// �������
	D3DXVec3Normalize(&(p->m_rot), &rot);	// ����
	p->m_fLength = fLength;			// ����
	p->m_fDiffusion = AngleToRadian(Diffusion);	// �g�U��(�p�x)
	p->m_pCor = Cor;				// �F
	p->m_nLifeParticle = nParticleLife;		// �p�[�e�B�N���̃��C�t
	// ���ԊǗ�
	p->m_nCreatSpan = nCreatSpan;	// �����Ԋu
	p->SetLifeSpan(nLife);

	return p;
}