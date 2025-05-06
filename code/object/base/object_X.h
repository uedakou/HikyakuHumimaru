//===========================================
// 
// �I�u�W�F�N�gX[renderer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT_X_H_
#define _OBJECT_X_H_

#include "object.h"

#define MAX_MODEL_X 1024
#define MAX_TEX_X 8	// 1���f���̃e�N�X�`���ő吔

class CModelX
{
public:
	typedef enum {
		TAG_NULL = 0,	// �^�O����
		TAG_STAGE,		// �X�e�[�W�I�u�W�F�N�g
		TAG_CHARACTER,	// �L�����N�^�[
		TAG_MAX
	}TAG;	// �ǂ��̂RD�I�u�W�F�N�g��
	CModelX();
	~CModelX();
	LPD3DXBUFFER GetBuffMtx() { return m_pBuffMat; }
	DWORD GetNumMat() { return m_dwNumMat; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	LPDIRECT3DTEXTURE9 GetTexture(int nCnt) { return m_pTexture[nCnt]; }
	void SetTag(TAG tag) { m_Tag = tag; }

	static void ReleaseTag(TAG tag);
	static void ReleaseAll();
	static int Load(const char* aFileName);
	static CModelX* GetModel(int nID);
private:
	// ���X�g
	static CModelX* m_pTop;	// �g�b�v
	static CModelX* m_pCur;	// �Ō��
	CModelX* m_pNext;		// ��
	CModelX* m_pPrev;		// �O

	LPD3DXBUFFER m_pBuffMat;					// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;							// �}�e���A���̐�
	LPD3DXMESH m_pMesh;							// ���b�V��(���_���)�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX_X];	// �v���C���[�̃e�N�X�`��[�e�N�X�`����]

	TAG m_Tag;
};

class CObjectX :public CObject
{
public:
	CObjectX();
	CObjectX(int nPriority);
	virtual ~CObjectX()		override;
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��

	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }

	void SetID(int nID);

	D3DXMATRIX GetMtx() { return m_mtxWorld; }

	int GetID() { return m_nID; }

	static CObjectX* creat(const char* aFileName);	// ����
	static CObjectX* creat(string aFileName);	// ����
protected:
private:
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���N�X

	static int m_nNum;	// X�I�u�W�F�N�g��
	int m_nID;	// ���f��ID


};






#endif // !_OBJECT_X_H_