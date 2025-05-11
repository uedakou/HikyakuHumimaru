//============================================
//
// �v���C���[[obstacles.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_
#include "base/object_X.h"

class CPlayer;	// �v���C���[
class CObstacles : public CObjectX
{
public:
	enum class TYPE {
		TALL = 0,	// ����
		HIGH,		// �����ʒu
		LOW,		// �Ⴂ�ʒu
		MAX
	};	// ���
	CObstacles();
	virtual ~CObstacles();
	virtual void Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	static CObstacles* clate(TYPE type, D3DXVECTOR3 pos);	// ����
private:	// �v���C�x�[�g
	// ���X�g���e�W�[
	
	class HitStrateg
	{
	public:
		HitStrateg() {}
		virtual ~HitStrateg() {}
		virtual void update(CPlayer* pPlayer) {}	// �X�V
	};
	// �w�̍�����Q���X�g���e�W�[
	class TallHitStrateg : public HitStrateg
	{
	public:
		TallHitStrateg();
		virtual ~TallHitStrateg();
		void update(CPlayer* pPlayer) override;	// �X�V
	};
	// �����ʒu�̏�Q���X�g���e�W�[
	class HighHitStrateg : public HitStrateg
	{
	public:
		HighHitStrateg();
		virtual ~HighHitStrateg();
		void update(CPlayer* pPlayer) override;	// �X�V
	};
	// �Ⴂ�̈ʒu��Q���X�g���e�W�[
	class LowHitStrateg : public HitStrateg
	{
	public:
		LowHitStrateg();
		virtual ~LowHitStrateg();
		void update(CPlayer* pPlayer) override;	// �X�V
	};
	HitStrateg* m_pHitStrateg;	// �q�b�g�X�g���e�W

	TYPE m_type;	// ���

	static const D3DXVECTOR3 s_Collision;	// �I�u�W�F�N�g�R���W����
};





#endif // !_OBSTACLES_H_