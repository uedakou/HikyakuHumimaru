//============================================
//
// 障害物(high)[obstacles_high.h]
// Author:Uedakou
// 
//============================================
#include "obstacles.h"
#ifndef _OBJECT_HIGH_H_
#define _OBJECT_HIGH_H_

class CObstaclesHigh : public CObstacles
{
public:
	virtual ~CObstaclesHigh();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	virtual void HitTest() override;	// 当たり判定

	static CObstaclesHigh* clate(D3DXVECTOR3 pos);	// 生成
private:	// プライベート
	CObstaclesHigh();

};

#endif // !_OBJECT_HIGH_H_