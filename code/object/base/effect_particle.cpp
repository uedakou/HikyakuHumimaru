//============================================
//
// エフェクト[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_particle.h"

/// <summary>
/// コンストラクタ
/// </summary>
CEffectParticle::CEffectParticle()
{
	m_move = { 0.0f, 0.0f, 0.0f };			// 動きを初期化
	m_cor = { 1.0f, 1.0f, 1.0f , 1.0f };	// 色を初期化
	m_nLife = 0;							// 寿命を初期化
	//SetSiz(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
}
/// <summary>
/// デストラクタ
/// </summary>
CEffectParticle::~CEffectParticle()
{
}
/// <summary>
/// 更新
/// </summary>
void CEffectParticle::Update()
{
	// ビルボード更新
	CObjectBillbord::Update();

	// 移動量加算
	AddPos(m_move);

	// 寿命を減らす
	m_nLife--;
	// 寿命が0なら死亡フラグを立てる
	if (m_nLife <= 0)
	{
		DeathFlag();
	}
}
void CEffectParticle::Draw()
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();// バーテックスバッファ取得
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();		// テクスチャ
	D3DXMATRIX mtxWorld = GetMaxWorld();	// ワールドマトリクス
	D3DXMATRIX mtxTrans;	// 計算用マトリクス
	D3DXMATRIX matView;	// ビューマトリクス

	// トランスフォームを取得
	X x = GetX();
	if (!pDevice) {
		// デバイスが無効な場合のエラーハンドリング
		return;
	}

	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ビューマトリクスの取得
	if (FAILED(pDevice->GetTransform(D3DTS_VIEW, &matView))) {
		// ビューマトリクス取得失敗時の処理
		return;
	}

	// ビューマトリクスの逆行列を計算
	if (D3DXMatrixInverse(&mtxWorld, NULL, &matView) == NULL) {
		// 逆行列計算失敗時の処理
		return;
	}
	// ワールドマトリクスの位置を初期化
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	// オブジェクトの位置を反映
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// 頂点バッファを設定
	if (pVtxBuff) {
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));
	}
	else {
		// 頂点バッファが無効な場合の処理
		return;
	}
	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// αブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャ
	pDevice->SetTexture(0, pTexture);
	//	ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
/// <summary>
/// パーティクルエフェクト生成
/// </summary>
/// <param name="pos">位置</param>
/// <param name="move">動き</param>
/// <param name="cor">色</param>
/// <param name="tex">テクスチャ</param>
/// <param name="nLife">寿命</param>
/// <returns>生成したポインタ</returns>
CEffectParticle* CEffectParticle::create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife)
{
	// インデックスを確保
	CEffectParticle* p = new CEffectParticle();

	p->SetPos(pos);	// 位置設定
	p->Init();		// 初期化
	p->SetColor(cor);	// 色設定
	p->SetTexture(tex.c_str());	// テクスチャ
	p->m_move = move;	// 動き設定
	p->m_nLife = nLife;	// 寿命

	// インデックスを返す
	return p;
}
