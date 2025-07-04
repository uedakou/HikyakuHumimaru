//============================================
//
// 2D当たり判定[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_2D_H_
#define _COLLISION_2D_H_
#include "collision.h"	// コリジョン

// 基底
class CCollision2D : public CCollision
{
public:
	typedef enum {
		Line = 0,	// 線
		Surface,	// 面
		Circle,		// 球
		MAX
	}TYPE;

	CCollision2D();
	~CCollision2D();
	TYPE GetType() { return type; }	// 種類取得

private:
	TYPE type;
};
#endif // !_COLLISION_2D_H_
