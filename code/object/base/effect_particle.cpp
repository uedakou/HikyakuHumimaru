//============================================
//
// �G�t�F�N�g[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_particle.h"

CEffectParticle::CEffectParticle()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_cor = { 0.0f, 0.0f, 0.0f , 0.0f };
	m_nLife = 0;
	//SetSiz(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
}

CEffectParticle::~CEffectParticle()
{
}

void CEffectParticle::Update()
{
	CObjectBillbord::Update();

	AddPos(m_move);
	m_nLife--;
	if (m_nLife <= 0)
	{
		DeathFlag();
	}
}
void CEffectParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();
	D3DXMATRIX mtxWorld = GetMaxWorld();	// ���[���h�}�g���N�X
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���N�X
	D3DXMATRIX matView;

	X x = GetX();
	if (!pDevice) {
		// �f�o�C�X�������ȏꍇ�̃G���[�n���h�����O
		return;
	}

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �r���[�}�g���N�X�̎擾
	if (FAILED(pDevice->GetTransform(D3DTS_VIEW, &matView))) {
		// �r���[�}�g���N�X�擾���s���̏���
		return;
	}

	// �r���[�}�g���N�X�̋t�s����v�Z
	if (D3DXMatrixInverse(&mtxWorld, NULL, &matView) == NULL) {
		// �t�s��v�Z���s���̏���
		return;
	}
	// ���[���h�}�g���N�X�̈ʒu��������
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	// �I�u�W�F�N�g�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	// ���[���h�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// ���_�o�b�t�@��ݒ�
	if (pVtxBuff) {
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));
	}
	else {
		// ���_�o�b�t�@�������ȏꍇ�̏���
		return;
	}
	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���u�����f�B���O
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�N�X�`��
	pDevice->SetTexture(0, pTexture);
	//	�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

CEffectParticle* CEffectParticle::create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife)
{
	CEffectParticle* p = new CEffectParticle();
	p->SetPos(pos);
	p->Init();
	p->SetColor(cor);
	p->SetTexture(tex.c_str());
	p->m_move = move;
	p->m_nLife = nLife;

	return p;
}
