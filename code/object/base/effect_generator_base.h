//============================================
//
// エフェクトジェネレーター[effect_generator_base.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR__BASE_H_
#define _EFFECT_GENERATOR__BASE_H_
#include "object.h"	// オブジェクト
class CEffectGeneratorBase : public CObject
{
public:
	CEffectGeneratorBase();
	virtual ~CEffectGeneratorBase();
	bool Init()		override;	// 初期化
	void Uninit()	override;	// 終了	
	void Update()	override;	// 更新
	void Draw()		override;	// 描画

	// 時間
	void SetLife(int nSpan) { m_nLife = nSpan; }	// 寿命設定
	int GetLife() { return m_nLife; }	// 寿命取得
	int GetCntTime() { return m_nCntLifeTime; }	// 経過時間取得

private:
	// 時間管理
	int m_nLife;	// エフェクトの寿命
	int m_nCntLifeTime;	// 現在の経過時間

};
#endif // !_EFFECT_GENERATOR__BASE_H_