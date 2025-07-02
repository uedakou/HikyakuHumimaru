//============================================
//
// エフェクトジェネレーター[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_generator_particle.h"	// エフェクトパーティクルジェネレーター
#include "effect_particle.h"	// エフェクトパーティクル
#include <iostream>
#include <random>

const string CEffectGeneratorParticle::s_aDefltTexture = "data/TEXTURE/shadow000.jpg";	// 初期エフェクトパーティクルテクスチャ
/// <summary>
/// コンストラクタ
/// </summary>
CEffectGeneratorParticle::CEffectGeneratorParticle()
{
	// 生成情報
	m_rot = { 0.0f, 0.0f, 0.0f };			// 向き
	m_fLength = 0.0f;						// 距離
	m_fDiffusion = 0.0f;					// 拡散量(角度)
	m_pCor = { 0.0f, 0.0f, 0.0f, 0.0f };	// 色
	m_aTexture = s_aDefltTexture;			// テクスチャ
	m_nLifeParticle = 0;					// パーティクルのライフ
	// 時間管理
	m_nCreatSpan = 0;		// 生成間隔
	m_nCntCreatTime = 0;	// 生成時間
}
/// <summary>
/// デストラクタ
/// </summary>
CEffectGeneratorParticle::~CEffectGeneratorParticle()
{
}
/// <summary>
/// 初期化
/// </summary>
/// <returns>true : 初期化成功</returns>
bool CEffectGeneratorParticle::Init()
{
	// エフェクトジェネレーターベース初期化
	CEffectGeneratorBase::Init();
	return true;
}
/// <summary>
/// 終了処理
/// </summary>
void CEffectGeneratorParticle::Uninit()
{
	// エフェクトジェネレーターベース終了
	CEffectGeneratorBase::Uninit();
}
/// <summary>
///  更新処理
/// </summary>
void CEffectGeneratorParticle::Update()
{
	// 死亡フラグが立っていなけらば
	if (IsDeathFlag() != true)
	{
		// エフェクトジェネレーターベース
		CEffectGeneratorBase::Update();

		// 生成カウントをカウントダウンする
		m_nCntCreatTime--;
		if (m_nCntCreatTime <= 0)
		{
			// カウントを戻す
			m_nCntCreatTime = m_nCreatSpan;
			// +-乱数
			int B = 1000.0f;	// 少数点以下の数字の乱数を入れるための変数
			D3DXVECTOR3 RandRotA = {};	// 角度の計算用格納変数
			// 範囲内で乱数を生成
			// 乱数生成器（シード付き）
			std::random_device rd;
			std::mt19937 gen(rd()); // メルセンヌ・ツイスタ
			// 乱数
			std::uniform_real_distribution<float> dist(-m_fDiffusion, m_fDiffusion);
			RandRotA.x = (dist(gen));
			RandRotA.y = (dist(gen));
			RandRotA.z = (dist(gen));

			RandRotA += m_rot;	// ジェネレーターの向きを加算
			D3DXVec3Normalize(&RandRotA, &RandRotA);	// ノーマライズ

			D3DXVECTOR3 move = RandRotA * m_fLength;	// 移動量を乗算
			//生成
			CEffectParticle::create(GetPos(), move, m_pCor, m_aTexture, m_nLifeParticle);
		}
	}
}
/// <summary>
/// 描画処理(ジェネレーターは描画しないため空)
/// </summary>
void CEffectGeneratorParticle::Draw()
{}
/// <summary>
/// テクスチャ設定
/// </summary>
/// <param name="aFileName">テクスチャファイルパス</param>
void CEffectGeneratorParticle::SetTexture(const char* aFileName)
{
	// デスフラグが立っていなけらば
	if (IsDeathFlag() != true)
	{
		m_aTexture = aFileName;
	}
}
/// <summary>
/// 生成
/// </summary>
/// <param name="rot">パーティクルのベクトル</param>
/// <param name="fLength">運動量</param>
/// <param name="Diffusion">拡散量</param>
/// <param name="Cor">色</param>
/// <param name="nParticleLife">パーティクルのがどれぐらい滞留するか</param>
/// <param name="nCreatSpan">生成間隔</param>
/// <returns>// 作成したオブジェクトを返す</returns>
CEffectGeneratorParticle* CEffectGeneratorParticle::create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan)
{
	// ジェネレーター用インスタンス確保
	CEffectGeneratorParticle* p = new CEffectGeneratorParticle();

	// インスタンス確保を失敗していたら
	if (!p)
	{
		return nullptr;
	}


	// 初期化
	if (!(p->Init()))// 初期化失敗時は解放して null を返す
	{
		delete p;
		p = nullptr;
		return nullptr;
	}

	// 生成情報
	D3DXVec3Normalize(&(p->m_rot),&rot);		// 向き
	p->m_fLength = fLength;						// 距離
	p->m_fDiffusion = AngleToRadian(Diffusion);	// 拡散量(角度)
	p->m_pCor = Cor;							// 色
	p->m_nLifeParticle = nParticleLife;			// パーティクルのライフ
	// 時間管理
	p->m_nCreatSpan = nCreatSpan;	// 生成間隔

	// 作成したオブジェクトを返す
	return p;
}
/// <summary>
/// 生成
/// </summary>
/// <param name="rot">パーティクルのベクトル</param>
/// <param name="fLength">運動量</param>
/// <param name="Diffusion">拡散量</param>
/// <param name="Cor">色</param>
/// <param name="nParticleLife">パーティクルのがどれぐらい滞留するか</param>
/// <param name="nCreatSpan">生成間隔</param>
/// <param name="nLife">ジェネレーター自体の寿命</param>
/// <returns></returns>
CEffectGeneratorParticle* CEffectGeneratorParticle::create(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife)
{
	// ジェネレーター用インスタンス確保
	CEffectGeneratorParticle* p = new CEffectGeneratorParticle();

	// 初期化
	p->Init();

	// 生成情報
	D3DXVec3Normalize(&(p->m_rot), &rot);	// 向き
	p->m_fLength = fLength;					// 距離
	p->m_fDiffusion = AngleToRadian(Diffusion);	// 拡散量(角度)
	p->m_pCor = Cor;						// 色
	p->m_nLifeParticle = nParticleLife;		// パーティクルのライフ
	// 時間管理
	p->m_nCreatSpan = nCreatSpan;			// 生成間隔
	p->SetLife(nLife);						// 寿命設定

	// インスタンスを返す
	return p;
}