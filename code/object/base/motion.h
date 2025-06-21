//===========================================
// 
// ���[�V����[motion.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "object_X.h"

#define MAX_MOTION (64)			// �ő僂�[�V����
#define MAX_KYE (32)			// �ő�L�[�t���[����
#define MAX_MOTION_MODEL (64)	// ���[�V�����Ɏg���郂�f����
#define MAX_PARTS (64)			// �ő�p�[�c��
/*
�S�̃��[�V�����Ǘ�
	���[�V����(�j���[�g����, �����Ȃ�)
		���݃L�[
		�L�[�t���[��
	�p�[�c
	���݃��[�V����
	

*/
class CPartsData
{
public:
	CPartsData();
	virtual ~CPartsData();

	void SetPosTarget(D3DXVECTOR3 pos) { m_x.pos = pos; }
	void SetRotTarget(D3DXVECTOR3 rot) { m_x.rot = rot; }
	void SetSclTarget(D3DXVECTOR3 siz) { m_x.scl = siz; }

	D3DXVECTOR3 GetPosTarget() { return m_x.pos; }
	D3DXVECTOR3 GetRotTarget() { return m_x.rot; }
	D3DXVECTOR3 GetSclTarget() { return m_x.scl; }
private:
	X m_x;	// �g�����X�t�H�[��

};

// �L�[�t���[��
class CKye
{
public:
	CKye();
	virtual ~CKye();
	void SetFrame(int nFrame) { m_nFrame = nFrame; }

	CPartsData* GetPartsData(int nParts) { return m_pParts[nParts]; }
	int GetFrame() { return m_nFrame; }
	CPartsData* createPartsData();

private:
	CPartsData* m_pParts[MAX_PARTS];	// �p�[�c
	int m_nFrame;
};

// ���[�V����
class CMotion 
{
public:
	CMotion();
	virtual ~CMotion();
	void SetNumKye(int nNumKye) { m_nNumKye = nNumKye; }
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void createKye();

	CKye* GetKye(int nKye) { return m_pKye[nKye]; }
	int GetNumKye() { return m_nNumKye; }
	bool GetLoop() { return m_bLoop; }
private:
	CKye* m_pKye[MAX_KYE];	// �L�[�t���[��
	int m_nNumKye;	// �L�[��
	bool m_bLoop;	// ���̃��[�V���������[�v���邩
};

// ���݃��[�V����
class CNowMotion
{
public:
	CNowMotion();
	virtual ~CNowMotion();
	// �ݒ�
	void SetMotion(int nMosyon) { m_nCntMotion = nMosyon; }		// ���[�V�����J�E���g
	void SetKye(int nKye) { m_nCntKye = nKye; }			// �L�[�J�E���g
	void SetFrame(int nFrame) { m_nCntFrame = nFrame; }		// �t���[��

	// �擾
	int GetMotion() { return m_nCntMotion; }	// ���[�V�����J�E���g
	int GetKye() { return m_nCntKye; }		// �L�[�J�E���g
	int GetFrame() { return m_nCntFrame; }		// �t���[��

	// �f�[�^�ǉ�
	void AddMotion(int nNum) { m_nCntMotion += nNum; }	// ���[�V�����J�E���g
	void AddKye(int nNum) { m_nCntKye += nNum; }		// �L�[�J�E���g
	void AddFrame(int nNum) { m_nCntFrame += nNum; }		// �t���[��

private:
	int m_nCntMotion;	// ���[�V�����J�E���g
	int m_nCntKye;		// �L�[�J�E���g
	int m_nCntFrame;	// �t���[��
};

// �p�[�c
class CParts : public CObjectX
{
public:
	CParts();
	CParts(int nPriority);
	virtual ~CParts()					override;
	virtual bool Init()		override; // ������
	virtual void Uninit()	override; // �I��
	virtual void Update()	override; // �X�V
	virtual void Draw()		override; // �`��


	// ��{�ʒu�ݒ�
	void SetBasicX(X x) {
		m_xBasic.pos = x.pos;
		m_xBasic.rot = x.rot;
		m_xBasic.scl = x.scl;
	}
	void SetBasicX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xBasic.pos = pos;
		m_xBasic.rot = rot;
		m_xBasic.scl = siz;
	}
	void SetBasicPos(D3DXVECTOR3 pos) { m_xBasic.pos = pos; }
	void SetBasicRot(D3DXVECTOR3 rot) { m_xBasic.rot = rot; }
	void SetBasicScl(D3DXVECTOR3 siz) { m_xBasic.scl = siz; }

	// �ǉ��ʒu
	void SetOffsetX(X x) {
		m_xOffset.pos = x.pos;
		m_xOffset.rot = x.rot;
		m_xOffset.scl = x.scl;
	}
	void SetOffsetX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz) {
		m_xOffset.pos = pos;
		m_xOffset.rot = rot;
		m_xOffset.scl = siz;
	}
	void SetOffsetPos(D3DXVECTOR3 pos) { m_xOffset.pos = pos; }
	void SetOffsetRot(D3DXVECTOR3 rot) { m_xOffset.rot = rot; }
	void SetOffsetScl(D3DXVECTOR3 siz) { m_xOffset.scl = siz; }

	// �����ݒ�
	void SetMoveX(X x, int nFrame) { SetMoveX(x.pos, x.rot, x.scl, nFrame); };
	void SetMoveX(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz, int nFrame); 

	// �f�[�^�ݒ�
	void SetParentID(int nParent) { m_nParent = nParent; }
	void SetParentMtx(D3DXMATRIX pParent) { m_mtxParent = pParent; }
	void SetDisplay(bool bDesplay) { m_bDisplay = bDesplay; }	// �\�����邩�ǂ���

	void SetMotion(int nMotion);

	// �ʒu�擾
	X GetBasicX() {
		return m_xBasic;
	}
	D3DXVECTOR3 GetBasicPos() { return m_xBasic.pos; }
	D3DXVECTOR3 GetBasicRot() { return m_xBasic.rot; }
	D3DXVECTOR3 GetBasicScl() { return m_xBasic.scl; }

	// �ǉ��ʒu
	X GetOffsetX() { return m_xOffset; }
	D3DXVECTOR3 GetOffsetPos() { return m_xOffset.pos; }
	D3DXVECTOR3 GetOffsetRot() { return m_xOffset.rot; }
	D3DXVECTOR3 GetOffsetScl() { return m_xOffset.scl; }

	// �f�[�^�擾
	int GetParentID() { return m_nParent; }				// �eID�擾
	D3DXMATRIX GetParentMtx() { return m_mtxParent; }	// �e�}�g���N�X�擾
	bool GetDisplay() { return m_bDisplay; }			// �\�����邩�ǂ���
	CNowMotion* GetNowMotion() { return m_pNowMotion; }	// ���݃��[�V����

	void SetDoMotion(bool bDoMotion) { m_bDoMotion = bDoMotion; }	// ���[�V�������邩�ݒ�

private:

	X m_xBasic;			// ��{�ʒu
	X m_xOffset;			// �ǉ��ʒu
	X m_xMove;			// ����

	int m_nParent;			// �eID
	D3DXMATRIX m_mtxParent;	// �e�}�g���N�X

	bool m_bDisplay;	// �\�����邩�ǂ���

	CNowMotion* m_pNowMotion;	// ���݃��[�V����

	bool m_bDoMotion;	// ���[�V�������邩�ǂ���
};

// ���[�V�����Ǘ�
class CObjectMotion : public CObject
{
public:
	CObjectMotion();
	virtual ~CObjectMotion()		override;
	virtual bool Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	
	// 1f�O�̈ʒu�ݒ�
	virtual void SetReleaseScene(bool bRelease) override;	// �V�[���Ń����[�X���邩
	void SetMotion(int nMotion);	// ���[�V�����ݒ�
	void SetMotionMove(bool bMotion) { m_bMotion = bMotion; }	// ���[�V�����𓮂������ǂ����ݒ�
	virtual void SetPartsNormalUpdate(bool bUpdate);	// �S�̂ōX�V���邩�ݒ�
	virtual void SetPartsPoseUpdate(bool bUpdate);		// �|�[�Y���X�V���邩�ݒ�
	virtual void SetPartsNormalDraw(bool bDraw);		// �S�̂ŕ`�悷�邩�ݒ�
	virtual void SetPartsPoseDraw(bool bDraw);			// �|�[�Y���`�悷�邩�ݒ�

	CMotion* GetMotion(int nNum) { return m_pMotion[nNum]; }// ���[�V�����f�[�^�擾
	int GetMotion() { return m_nNowMotion; }	// ���݃��[�V����
	int GetNumParts() { return m_nParts; }
	CParts* GetParts(int nNum) { return m_pParts[nNum]; }	// �p�[�c�擾
	static CObjectMotion* create(const char* FileName);
	static CObjectMotion* create(string FileName);

protected:
	bool Load(const char* aFileName);	// ���[�V�����ǂݍ���

	virtual int GetNextMotion() { return 0; };	// ���擾
private:
	void createMotion();// ���[�V��������
private:
	int m_nModel;							// ���f����

	int m_nNumMotion;						// ���[�V������
	CMotion* m_pMotion[MAX_MOTION];	// ���[�V�����f�[�^

	int m_nParts;				// �p�[�c��
	CParts* m_pParts[MAX_PARTS];

	int m_nNextMotion;	// �����[�V����
	int m_nNowMotion;	// ���݃��[�V����

	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���N�X

	bool m_bMotion;	// ���[�V�����𓮂������ǂ���

	static const bool s_bMotion;	// ���[�V�����𓮂������ǂ����̏����ݒ�
};




#endif // !_MOTION_H_