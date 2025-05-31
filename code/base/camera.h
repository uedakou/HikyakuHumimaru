//============================================
//
// �J����[camera.h]
// Author:Uedakou
// 
//============================================
#ifndef _CUMERA_H_
#define _CUMERA_H_
#include "main.h"


#define s_bCumeraDataDraw (false)





class CText;
class CCamera
{
public:	// �萔

	enum class ProjectionType {
		Perspective = 0,	// �������e
		Orthographic,		// ���s���e
		MAX
	};

	static const float POS_CAMERA;		// ���_�ƒ����_�̋���
	static const ProjectionType CAMERA_TYPE;		// ���e����
	static const bool CAMERA_CONTROLLER;// �J�����ŃR���g���[���[�����邩
	static const D3DXVECTOR3 CAMERA_V;	// �J�����ʒu�擾
	static const D3DXVECTOR3 CAMERA_ROT;	// �J�����ʒu�擾
	static const D3DXVECTOR3 CAMERA_U;	// �����
	static const float MOVE_SPEED;	// �ړ����x
	static const float MOVE_SPEED_FAST;// �V�t�g�ړ����x

public:	// �֐�
	CCamera();
	~CCamera();
	HRESULT Init(void);		//������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void SetCamera(void);	// �`��

	// �ݒ�
	void SetNomal() { m_posV = {}; m_posR = {}; m_rot = {}; }	// �J�����m�[�}���C�Y

	void SetPosV(D3DXVECTOR3 pos) { m_posV = pos; CameraSetR(); }	// �J�����ʒu�ݒ�
	void SetPosVX(float x) { m_posV.x = x; CameraSetR(); }	// �J�����ʒu�ݒ�
	void SetPosVY(float y) { m_posV.y = y; CameraSetR(); }	// �J�����ʒu�ݒ�
	void SetPosVZ(float z) { m_posV.z = z; CameraSetR(); }	// �J�����ʒu�ݒ�

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; CameraSetR(); }// �J���������ݒ�
	void SetRotX(float x) { m_rot.x = x; CameraSetR(); }	// �J���������ݒ�
	void SetRotY(float y) { m_rot.y = y; CameraSetR(); }	// �J���������ݒ�
	void SetRotZ(float z) { m_rot.z = z; CameraSetR(); }	// �J���������ݒ�

	// �擾
	D3DXVECTOR3 GetPosV() { return m_posV; CameraSetR(); }	// �J�����ʒu�擾
	D3DXVECTOR3 GetPosR() { return m_posR; CameraSetR(); }	// �J���������_�ʒu�擾
	D3DXVECTOR3 GetRot() { return m_rot; CameraSetR(); }		// �J���������擾

	//�@���Z
	void AddPosVandRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot) { m_posV += pos; m_rot += rot; CameraSetR(); }	// �J�����ʒu�ƌ������Z

	void AddPosV(D3DXVECTOR3 pos) { m_posV += pos; CameraSetR(); }	// �J�����ʒu���Z
	void AddPosVX(float x) { m_posV.x += x; CameraSetR(); }	// �J�����ʒu���Z
	void AddPosVY(float y) { m_posV.y += y; CameraSetR(); }	// �J�����ʒu���Z
	void AddPosVZ(float z) { m_posV.z += z; CameraSetR(); }	// �J�����ʒu���Z

	void AddRot(D3DXVECTOR3 rot) { m_rot += rot; CameraSetR(); }	// �J�����������Z
	void AddRotX(float x) { m_rot.x += x; CameraSetR(); }	// �J�����������Z
	void AddRotY(float y) { m_rot.y += y; CameraSetR(); }	// �J�����������Z
	void AddRotZ(float z) { m_rot.z += z; CameraSetR(); }	// �J�����������Z

	bool IsCameraControllreFpllow()// ���݃J�������R���g���[�����邩
	{
		return m_bCumeraController;
	}

	void DrawCamera();		// �J�������`��
private:	// �֐�
	void Controller();	// ����
	void CameraSetR();

private:
	// �J�����^�C�v���X�g���e�W�[
	class ProjectionStrategy {
	public:
		ProjectionStrategy() {};
		virtual void Projection(D3DXMATRIX* mtx) = 0;	// ���e
	};
	// �������e����
	class ProjectionPerspectiveStrategy : public ProjectionStrategy {
	public:
		ProjectionPerspectiveStrategy();
		virtual void Projection(D3DXMATRIX* mtx);	// ���e
	private:
		float m_fFov;	// ����p
		float m_fNear;	// �߃N���b�v��(�j�A)
		float m_fFar;	// ���N���b�v��(�t�@�[)
	public:
		static const float PERSPECTIVE_FOV;		// ����p
		static const float PERSPECTIVE_NEAR;	// �߃N���b�v��
		static const float PERSPECTIVE_FAR;		// ���N���b�v��
	};
	// ���s���e
	class ProjectionOrthographicStrategy : public ProjectionStrategy {
	public:
		ProjectionOrthographicStrategy();
		virtual void Projection(D3DXMATRIX* mtx);	// ���e
	private:

		float m_fNear;	// �߃N���b�v��(�j�A)
		float m_fFar;	// ���N���b�v��(�t�@�[)
	public:

		static const float PERSPECTIVE_NEAR;	// �߃N���b�v��
		static const float PERSPECTIVE_FAR;		// ���N���b�v��
	};

private:	// �ϐ�
	CCamera::ProjectionType m_CameraType;			// �J���������ߓ��e�������e��
	bool m_bCumeraController;	// �J�����̃R���g���[�����ł��邩

	D3DXVECTOR3 m_posV;			// �J�����ʒu
	D3DXVECTOR3 m_vecU;			// �㑤
	D3DXVECTOR3 m_rot;			// ����
	float m_fLeng;				// ���_�ƒ����_�̋���
	D3DXVECTOR3 m_posR;			// �����_�ʒu

	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����s��
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X

	D3DXVECTOR3 m_rotTarget;	// ����(90�x��)
	bool m_bRotTarget;			// �^�[�Q�b�g�Ɍ����邩

	float m_fMoveSpeed;	// �ړ����x
	float m_fMoveFastSpeed;// �V�t�g�ړ����x

	CText* m_pText;

	ProjectionStrategy* m_pCameraStrategy;	// ���e
};

#endif // !_CUMERA_H_