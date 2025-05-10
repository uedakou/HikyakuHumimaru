//============================================
//
// プレイヤー[obstacles.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_
#include "base/object_X.h"

class CObstacles : public CObjectX
{
public:
	enum class TYPE {
		TALL = 0,	// 高壁
		HIGH,		// 高い位置
		LOW,		// 低い位置
		MAX
	};	// 種類
	CObstacles();
	~CObstacles();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	static CObstacles* clate(TYPE type, D3DXVECTOR3 pos);	// 生成
private:	// プライベート
	// 基底ストラテジー
	class UpdatStrateg
	{
	public:
		UpdatStrateg() {}
		~UpdatStrateg() {}
		CObstacles* update() {}	// 更新
	};
	// 背の高い障害物ストラテジー
	class TALLUpdatStrateg : public UpdatStrateg
	{
	public:
		TALLUpdatStrateg();
		~TALLUpdatStrateg();
		CObstacles* update();	// 更新
	};
	// 高い位置の障害物ストラテジー
	class HIGHUpdatStrateg : public UpdatStrateg
	{
	public:
		HIGHUpdatStrateg();
		~HIGHUpdatStrateg();
		CObstacles* update();	// 更新
	};
	// 低いの位置障害物ストラテジー
	class LOWUpdatStrateg : public UpdatStrateg
	{
	public:
		LOWUpdatStrateg();
		~LOWUpdatStrateg();
		CObstacles* update();	// 更新
	};





	TYPE m_type;	// 種類

	static const D3DXVECTOR3 s_Collision;	// オブジェクトコリジョン
};





#endif // !_OBSTACLES_H_