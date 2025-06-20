//============================================
//
// �J����[camera.cpp]
// Author:Uedakou
// 
//============================================
#include "camera.h"	// �J����
#include "manager.h"	// �}�l�[�W���[
#include <strsafe.h>	// StringCbPrintf���g�p����ɂ̂ɕK�v
#include "../object/Base/object.h"	// �I�u�W�F�N�g
#include "../object/base/text.h"

// �������e
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_FOV = 45.0f;
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_NEAR = 50.0f;
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_FAR = 10000.0f;

// ���s���e
const float CCamera::ProjectionOrthographicStrategy::PERSPECTIVE_NEAR = 50.0f;
const float CCamera::ProjectionOrthographicStrategy::PERSPECTIVE_FAR = 10000.0f;


// �J�����萔
const float CCamera::POS_CAMERA = 100.0f;	// ���_�ƒ����_�̋���
const CCamera::ProjectionType CCamera::CAMERA_TYPE = CCamera::ProjectionType::Perspective;	// ���e����
const bool CCamera::CAMERA_CONTROLLER = false;	// �J�����ŃR���g���[���[�����邩
const D3DXVECTOR3 CCamera::CAMERA_V = D3DXVECTOR3(0.0f, 40.0f, -POS_CAMERA);	// �J�����ʒu�擾
const D3DXVECTOR3 CCamera::CAMERA_ROT = D3DXVECTOR3(1.5f, 0.0f, 0.0f);	// �J���������擾
const D3DXVECTOR3 CCamera::CAMERA_U = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �����
const float CCamera::MOVE_SPEED = 10.0f;	// �ړ����x
const float CCamera::MOVE_SPEED_FAST = 50.0f;// �V�t�g�ړ����x

//============================================
// �R���X�g
//============================================
CCamera::CCamera()
{
	m_CameraType = CAMERA_TYPE;				// �J�������ߓ��e
	m_bCumeraController = CAMERA_CONTROLLER;			// �v���C���[�Ǐ]

	m_posV = CAMERA_V;	// ���_
	m_vecU = CAMERA_U;	// �����
	m_rot = CAMERA_ROT;	// ����
	m_fLeng = POS_CAMERA;	// ���_�ƒ����_�̋���

	m_posR.x = cos(m_rot.x) + sin(m_rot.y) * m_fLeng;	// �����_
	m_posR.z = cos(m_rot.x) + cos(m_rot.y) * m_fLeng;	// �����_
	m_posR.y = sin(m_rot.x) * m_fLeng;	// �����_


	m_rotTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����(�ڕW)
	m_bRotTarget = false;						// �␳��]������

	m_fMoveSpeed = MOVE_SPEED;
	m_fMoveFastSpeed = MOVE_SPEED_FAST;

	m_pText = nullptr;

	m_pCameraStrategy = new ProjectionPerspectiveStrategy();
}
//============================================
// �f�X�g��
//============================================
CCamera::~CCamera()
{

}
//============================================
// ����������
//============================================
HRESULT CCamera::Init(void)
{
#if _DEBUG
	m_pText = CText::creat();
	m_pText->SetReleaseScene(false);
#endif //! _DEBUG
	return S_OK;
}
//============================================
// �I������
//============================================
void CCamera::Uninit(void)
{}
//============================================
// �X�V����
//============================================
void CCamera::Update(void)
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();	// �L�[�{�[�h����
	if (pKey->GetTrigger(DIK_F2))
	{
		m_bCumeraController = m_bCumeraController ? false : true;
	}
	if (m_bCumeraController)
	{
		Controller();
		// �l���␳��]
		if (m_bRotTarget == true)
		{
			// �l���␳��]�K��
			float fRotY = (m_rotTarget.y - m_rot.y);
			if (fRotY >= D3DX_PI)
			{
				fRotY -= TAU;
			}
			else if (fRotY <= -D3DX_PI)
			{
				fRotY += TAU;
			}

			m_rot.y += fRotY * 0.1f;

			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y -= TAU;
			}
			else if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
			// ��]������������
			if (m_rot.y - m_rotTarget.y <= 0.005f &&
				m_rot.y - m_rotTarget.y >= 0.005f)
			{
				m_bRotTarget = false;
			}
		}
	}
	CameraSetR();
	// �J�������e�L�X�g�\��
#if _DEBUG

#if s_bCumeraDataDraw
	DrawCamera();
#endif // s_bCumeraDataDraw
#endif // _DEBUG
}
//============================================
// �`�揈��
//============================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^

	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
#if 1
	// �v���W�F�N�V�����}�g���N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	// ����p�iFOV�j
		(float)SCREEN_W / (float)SCREEN_H,	// �A�X�y�N�g��i�� / �c�j
		10,		// �߃N���b�v��
		10000);	// ���N���b�v��
#else
	m_pCameraStrategy->Projection(&m_mtxProjection);
#endif // 0


	//switch (m_CameraType)
	//{
	//case ProjectionType::Perspective:
	//	// ���ߓ��e
	//	Projection()
	//	break;
	//case ProjectionType::Orthographic:
	//	// �����e
	//	break;
	//default:
	//	break;
	//}
#if _DEBUG


#endif // _DEBUG
	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	// �r���[�}�g���N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//============================================
// �J�������`��
//============================================
void CCamera::DrawCamera()
{
	char aStr[MAX_TXT];
	sprintf_s(aStr, sizeof(aStr), "CameraV Pos:X%f Y%f Z%f\nCameraR Pos:X%f Y%f Z%f\nCamera Rot:X%f Y%f Z%f\n", m_posV.x, m_posV.y, m_posV.z, m_posR.x, m_posR.y, m_posR.z, m_rot.x, m_rot.y, m_rot.z);
	if (m_pText != nullptr)
	{
		m_pText->SetText(aStr);
	}
}
//============================================
// ����
//============================================
void CCamera::Controller()
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();
	// ��]
	if (pKey->GetTrigger(DIK_Q))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y <= 0.0f + 0.005f &&
				m_rot.y > -(D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = -(D3DX_PI * 0.5f);
			}
			else if (m_rot.y <= -(D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > -D3DX_PI + 0.005f)
			{
				m_rotTarget.y = -D3DX_PI;
			}
			else if (m_rot.y <= -D3DX_PI + 0.005f ||
				m_rot.y > (D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y <= (D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > 0.0f + 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_Q) &&
		m_bRotTarget == false)
	{
		m_rot.y -= 0.05f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += TAU;
		}
	}
	else if (pKey->GetTrigger(DIK_E))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y >= 0.0f - 0.005f &&
				m_rot.y < (D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= D3DX_PI * 0.5f - 0.005f &&
				m_rot.y < D3DX_PI - 0.005f)
			{
				m_rotTarget.y = D3DX_PI;
			}
			else if (m_rot.y >= D3DX_PI - 0.005f ||
				m_rot.y < -(D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = -D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= -(D3DX_PI * 0.5f) - 0.005f &&
				m_rot.y < 0.0f - 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_E) &&
		m_bRotTarget == false)
	{
		m_rot.y += 0.05f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= TAU;
		}
	}
	if (pKey->GetRepeat(DIK_R))
	{
		if (m_rot.x < D3DX_PI)
		{
			m_rot.x -= 0.05f;
		}
	}
	else if (pKey->GetRepeat(DIK_F))
	{
		if (m_rot.x > 0)
		{
			m_rot.x += 0.05f;
		}
	}
	// �ړ�
	if (pKey->GetRepeat(DIK_LSHIFT))
	{
		if (pKey->GetRepeat(DIK_W))
		{// �O���ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ����ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else
			{// ��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// ����ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ���O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E�O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else
			{// �O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// ���ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// �E�ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		// �㉺
		if (pKey->GetRepeat(DIK_SPACE))
		{// �㏸
			m_posV.y += m_fMoveFastSpeed;
		}
		else if (pKey->GetRepeat(DIK_LCONTROL))
		{// ���~
			m_posV.y -= m_fMoveFastSpeed;
		}
	}
	else
	{
		if (pKey->GetRepeat(DIK_W))
		{// �O���ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ����ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else
			{// ��ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// ����ړ�
			if (pKey->GetRepeat(DIK_A))
			{// ���O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// �E�O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else
			{// �O�ړ�
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// ���ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// �E�ړ�
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
	}

	// �㉺
	if (pKey->GetRepeat(DIK_SPACE))
	{// �㏸
		m_posV.y += 10.0f;
	}
	else if (pKey->GetRepeat(DIK_LCONTROL))
	{// ���~
		m_posV.y -= 10.0f;
	}
}
void CCamera::CameraSetR()
{
	m_posR.x = m_posV.x + cosf(m_rot.x - (D3DX_PI * 0.5f)) * sinf(m_rot.y) * POS_CAMERA;
	m_posR.y = m_posV.y + sinf(m_rot.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
	m_posR.z = m_posV.z + cosf(m_rot.x - (D3DX_PI * 0.5f)) * cosf(m_rot.y) * POS_CAMERA;
}
//============================================
// �������e
//============================================
CCamera::ProjectionPerspectiveStrategy::ProjectionPerspectiveStrategy()
{
	m_fFov = PERSPECTIVE_FOV;
	m_fNear = PERSPECTIVE_NEAR;
	m_fFar = PERSPECTIVE_FAR;
}
void CCamera::ProjectionPerspectiveStrategy::Projection(D3DXMATRIX* mtx)
{
	// �v���W�F�N�V�����}�g���N�X���쐬
	D3DXMatrixPerspectiveFovLH(mtx,
		D3DXToRadian(m_fFov),	// ����p�iFOV�j
		(float)SCREEN_W / (float)SCREEN_H,	// �A�X�y�N�g��i�� / �c�j
		m_fNear,		// �߃N���b�v��
		m_fFar);	// ���N���b�v��
}

CCamera::ProjectionOrthographicStrategy::ProjectionOrthographicStrategy()
{
	m_fNear = PERSPECTIVE_NEAR;
	m_fFar = PERSPECTIVE_FAR;
}

void CCamera::ProjectionOrthographicStrategy::Projection(D3DXMATRIX* mtx)
{
	D3DXMatrixOrthoLH(
		mtx,
		(float)SCREEN_W,
		(float)SCREEN_H,
		m_fNear,
		m_fFar);
}
