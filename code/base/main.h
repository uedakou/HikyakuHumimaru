//===========================================
// 
// ���C��[main.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MAIN_H_	// ���̃}�N����`����ĂȂ��Ȃ�
#define _MAIN_H_	// ��d�C���N���[�h�h�~�̃}�N��
#include "pch.h"	// �v���R���p�C���ς݃w�b�_


class CApplication
{
public:
	CApplication();
	~CApplication();

	bool Init(HINSTANCE hInstance, int nCmdShow); // ����������
	void Uninit();	// �������
	void Run();		// ���C�����[�v
	void OnKeyDown(WPARAM key);	// �L�[�{�[�h���͂ɑ΂��鏈��

private:
	HWND m_hWnd;				// �A�v���P�[�V�����̃E�B���h�E�n���h��
	WNDCLASSEX m_wcex;			// �E�B���h�E�N���X���\����
	MSG m_msg;					// ���b�Z�[�W�\����
	DWORD m_dwExecLastTime;		// �Ō�ɏ������s�������ԁims�j
	DWORD m_dwFPSLostTime;		// �Ō��FPS���v���������ԁims�j
	DWORD m_dwFrameCount;		// �t���[�����J�E���g�iFPS�v���p�j
};
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
int GetFPS();	// FPS�擾

#endif // _MAIN_H_