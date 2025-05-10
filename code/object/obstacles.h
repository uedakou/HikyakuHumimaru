//============================================
//
// �v���C���[[obstacles.h]
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
		TALL = 0,	// ����
		HIGH,		// �����ʒu
		LOW,		// �Ⴂ�ʒu
		MAX
	};	// ���
	CObstacles();
	~CObstacles();
	virtual void Init() override;	// ������
	virtual void Uninit() override;	// �I��
	virtual void Update() override;	// �X�V
	virtual void Draw() override;	// �`��

	static CObstacles* clate(TYPE type, D3DXVECTOR3 pos);	// ����
private:	// �v���C�x�[�g
	// ���X�g���e�W�[
	class UpdatStrateg
	{
	public:
		UpdatStrateg() {}
		~UpdatStrateg() {}
		CObstacles* update() {}	// �X�V
	};
	// �w�̍�����Q���X�g���e�W�[
	class TALLUpdatStrateg : public UpdatStrateg
	{
	public:
		TALLUpdatStrateg();
		~TALLUpdatStrateg();
		CObstacles* update();	// �X�V
	};
	// �����ʒu�̏�Q���X�g���e�W�[
	class HIGHUpdatStrateg : public UpdatStrateg
	{
	public:
		HIGHUpdatStrateg();
		~HIGHUpdatStrateg();
		CObstacles* update();	// �X�V
	};
	// �Ⴂ�̈ʒu��Q���X�g���e�W�[
	class LOWUpdatStrateg : public UpdatStrateg
	{
	public:
		LOWUpdatStrateg();
		~LOWUpdatStrateg();
		CObstacles* update();	// �X�V
	};





	TYPE m_type;	// ���

	static const D3DXVECTOR3 s_Collision;	// �I�u�W�F�N�g�R���W����
};





#endif // !_OBSTACLES_H_