//============================================
//
// ��Q��(high)[obstacles_high.h]
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
	virtual void Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	virtual void HitTest() override;	// �����蔻��

	static CObstaclesHigh* clate(D3DXVECTOR3 pos);	// ����
private:	// �v���C�x�[�g
	CObstaclesHigh();

};

#endif // !_OBJECT_HIGH_H_