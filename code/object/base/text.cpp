//===========================================
// 
// �e�L�X�g[text.cop]
// Auther:UedaKou
// 
//===========================================
#include "text.h"
#include <strsafe.h>	// StringCbPrintf���g�p����ɂ̂ɕK�v
#include "../../base/pch.h"		// �v���R���p�C��
#include "../../base/manager.h"	// �}�l�[�W���[
string CText::m_aFontList[Max] = {
	{"Terminal"},
};

const int	CText::s_nHyde = 18;	// ��������	
const UINT	CText::s_nWide = 0;	// ������
const UINT	CText::s_nBold = 0;	// ��������
const UINT	CText::s_nMip = 0;		// �~�b�v���x��	
const bool	CText::s_bItalic = FALSE;	// �������Α̂�
const DWORD	CText::s_nFont = SHIFTJIS_CHARSET;		// �t�H���g
const DWORD	CText::s_nSize = OUT_DEFAULT_PRECIS;	// �����T�C�Y(�ύX�s��)
const DWORD	CText::s_nPitch = DEFAULT_PITCH;		// �s�b�`
const CText::Type	CText::s_type = Type::Terminal;		// ���̂��܂ޕ�����
const RECT	CText::s_Space = { 0, 0, SCREEN_H , SCREEN_W };	// �\���̈�
const D3DXCOLOR CText::s_pCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
const string	CText::s_aText = "�e�L�X�g����͂��Ă�������";		// �e�L�X�g

//============================================
// �R���X�g���N�^
//============================================
CText::CText()
{
	m_pFont = nullptr;
	m_nHyde = s_nHyde;		// ��������
	m_nWide = s_nWide;		// ������
	m_nBold = s_nBold;		// ��������
	m_nMip = s_nMip;		// �~�b�v���x��
	m_bItalic = s_bItalic;	// �������Α̂�
	m_nFont = s_nFont;		// �t�H���g
	m_nSize = s_nSize;		// �����T�C�Y(�ύX�s��)
	m_nPitch = s_nPitch;	// �s�b�`
	m_type = s_type;		// ���̖����܂ޕ�����
	m_Space = s_Space;		// �̈�
	m_pCol = s_pCol;		// �����F
	m_aText = s_aText;		// �\���e�L�X�g

	CObject::SetType(CObject::TYPE::TEXT);
}
CText::CText(int nPriorithi) :
	CObject(nPriorithi)
{
	m_pFont = nullptr;
	m_nHyde = s_nHyde;		// ��������
	m_nWide = s_nWide;		// ������
	m_nBold = s_nBold;		// ��������
	m_nMip = s_nMip;		// �~�b�v���x��
	m_bItalic = s_bItalic;	// �������Α̂�
	m_nFont = s_nFont;		// �t�H���g
	m_nSize = s_nSize;		// �����T�C�Y(�ύX�s��)
	m_nPitch = s_nPitch;	// �s�b�`
	m_type = s_type;		// ���̖����܂ޕ�����
	m_Space = s_Space;		// �̈�
	m_pCol = s_pCol;		// �����F
	m_aText = s_aText;		// �\���e�L�X�g

	CObject::SetType(CObject::TYPE::TEXT);

}
//============================================
// �f�X�g���N�^
//============================================
CText::~CText()
{
	if (m_pFont != nullptr) {
		m_pFont->Release();
		m_pFont = nullptr;
	}
}
//============================================
// ������
//============================================
void CText::Init()
{
	SetData();
}
//============================================
// �I��
//============================================
void CText::Uninit()
{
}
//============================================
// �X�V
//============================================
void CText::Update()
{
}
//============================================
// �`��
//============================================
void CText::Draw()
{
	if (m_aText != "")
	{
		// �e�L�X�g�̕`��
		if (m_pFont != nullptr)
		{
			m_pFont->DrawText(nullptr, m_aText.c_str(), -1, &m_Space, DT_LEFT, m_pCol);
		}
	}
}

//============================================
// �ݒ蔽�f
//============================================
void CText::SetData()
{
	CManager* instance = CManager::GetInstance();	// �C���X�^���X
	LPDIRECT3DDEVICE9 pDevice = instance->GetRenderer()->GetDevice();	// �f�o�C�X
	// �f�o�b�O�\���p�t�H���g�̐���
	HRESULT hr = D3DXCreateFont(pDevice,	// �f�o�C�X
		m_nHyde,						// �^(int)	�_���P�ʂł̕����̍����B
		m_nWide,						// �^(UINT)	�_���P�ʂł̕����̕��B
		m_nBold,						// �^(UINT)	���̂̑����B 1 �̗�͑����ł��B
		m_nMip,							// �^(UInt)	�~�b�v�}�b�v ���x���̐��B
		m_bItalic,						// �^(BOOL)		�Α̃t�H���g�̏ꍇ�� True�A����ȊO�̏ꍇ�� false�B
		m_nFont,						// �^(DWORD)	�t�H���g�̕����Z�b�g�B
		m_nSize,						// �^(DWORD)	Windows ���ړI�̃t�H���g �T�C�Y�Ɠ��������ۂ̃t�H���g�Əƍ�������@���w�肵�܂��B ���Ƃ��΁AOUT_TT_ONLY_PRECIS���g�p���āA��� TrueType �t�H���g���擾�ł���悤�ɂ��܂��B
		DEFAULT_QUALITY,				// �^(DWORD)	Windows ���ړI�̃t�H���g�Ǝ��ۂ̃t�H���g����v��������@���w�肵�܂��B ���X�^�[ �t�H���g�ɂ̂ݓK�p����ATrueType �t�H���g�ɂ͉e�����܂���B
		m_nPitch,						// �^(DWORD)	�s�b�`�ƃt�@�~�� �C���f�b�N�X�B
		m_aFontList[m_type].c_str(),	// ���(LPCTSTR)	���̖����܂ޕ�����B �R���p�C���ݒ�� Unicode ���K�v�ȏꍇ�A�f�[�^�^ LPCTSTR �� LPCWSTR �ɉ�������܂��B ����ȊO�̏ꍇ�A������f�[�^�^�� LPCSTR �ɉ�������܂��B
		&m_pFont);						// ���(LPD3DXFONT*)	�쐬���ꂽ�t�H���g �I�u�W�F�N�g��\�� ID3DXFont �C���^�[�t�F�C�X�ւ̃|�C���^�[��Ԃ��܂��B


	if (FAILED(hr)) {
		// �G���[�����i���O�o�͂��O�����Ȃǁj
		Beep(1200, 300);
		//std::cerr << "Failed to create font! HRESULT: " << hr << std::endl;
		m_pFont = nullptr;
	}
}

/// <summary>
/// �S�`��p�ݒ���Đݒ�
/// </summary>
/// <param name="nH">		�����̍����B	</param>		
/// <param name="nW">		�����̕��B	</param>		
/// <param name="nBold">	���̂̑����B	</param>	
/// <param name="nMip">		�~�b�v�}�b�v ���x���̐��B	</param>		
/// <param name="bItalic">	�Α̃t�H���g�̏ꍇ�� True�A����ȊO�̏ꍇ�� false�B	</param>	
/// <param name="nFont">	�t�H���g�̕����Z�b�g�B</param>	
/// <param name="nSize">	Windows ���ړI�̃t�H���g �T�C�Y�Ɠ��������ۂ̃t�H���g�Əƍ�������@���w�肵�܂��B</param>	
/// <param name="nPitch"	�s�b�`�ƃt�@�~�� �C���f�b�N�X�B></param>	
/// <param name="type">		���̖����܂ޕ�����</param>	
void CText::SetAll(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type)
{
	m_nHyde = nH;
	m_nWide = nW;
	m_nBold = nBold;
	m_nMip = nMip;
	m_bItalic = bItalic;
	m_nFont = nFont;
	m_nSize = nSize;
	m_nPitch = nPitch;
	m_type = type;
	SetData();
}
/// <summary>
/// �Œ�e�L�X�g��ݒ�
/// ��ɂ����Print �`��\
/// </summary>
/// <param name="text"> �\���e�L�X�g</param>
void CText::SetText(const char* text)
{
	m_aText = text;
}

void CText::SetText(string text)
{
	m_aText = text;
}
//===============================================
//�t�H���g�擾
//===============================================
LPD3DXFONT CText::GetFont()
{
	return m_pFont;
}
//===============================================
// ����
//===============================================
/// <summary>
/// �e�L�X�g����
/// </summary>
/// <returns>���������e�L�X�g�̃|�C���^</returns>
CText* CText::creat()
{
	CText* pTex = new CText();

	pTex->Init();

	return pTex;
}
/// <summary>
/// �e�L�X�g����
/// </summary>
/// <param name="nHyde">�����̑傫��</param>
/// <param name="nWide">�����̕�</param>
/// <param name="nBold">�����̑���</param>
/// <param name="nMip">�~�b�v���x��</param>
/// <param name="bItalic">�Α̂Ȃ�true�Ⴄ�Ȃ�false</param>
/// <returns>���������e�L�X�g�̃|�C���^</returns>
CText* CText::creat(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic)
{
	CText* pTex = new CText();

	pTex->m_nHyde = nHyde;
	pTex->m_nWide = nWide;
	pTex->m_nBold = nBold;
	pTex->m_nMip = nMip;
	pTex->m_bItalic = bItalic;
	pTex->Init();

	return pTex;
}
/// <summary>
/// �e�L�X�g����
/// </summary>
/// <param name="nHyde">�����̑傫��</param>
/// <param name="nWide">�����̕�</param>
/// <param name="nBold">�����̑���</param>
/// <param name="nMip">�~�b�v���x��</param>
/// <param name="bItalic">�Α̂Ȃ�true�Ⴄ�Ȃ�false</param>
/// <param name="nFont">�t�H���g�����Z�b�g</param>
/// <param name="nSize">Windows ���ړI�̃t�H���g �T�C�Y�Ɠ��������ۂ̃t�H���g�Əƍ�������@���w�肵�܂�</param>
/// <param name="nPitch">�s�b�`�ƃC���f�b�N�X</param>
/// <param name="type">����</param>
/// <returns>���������e�L�X�g�̃|�C���^</returns>
CText* CText::creat(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, Type type)
{
	CText* pTex = new CText();

	pTex->m_nHyde = nHyde;
	pTex->m_nWide = nWide;
	pTex->m_nBold = nBold;
	pTex->m_nMip = nMip;
	pTex->m_bItalic = bItalic;
	pTex->m_nFont = nFont;
	pTex->m_nSize = nSize;
	pTex->m_nPitch = nPitch;
	pTex->m_type = type;

	pTex->Init();

	return pTex;
}