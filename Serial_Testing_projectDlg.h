
// Serial_Testing_projectDlg.h: 헤더 파일
//
#pragma once
#include "CommThread.h"

// CSerialTestingprojectDlg 대화 상자
class CSerialTestingprojectDlg : public CDialogEx
{
// 생성입니다.
public:
	CSerialTestingprojectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_TESTING_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	CWinThread* SerialThread;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CCommThread cComThread;

protected:
	CString serialPort;
	DWORD baudRate;
	BYTE dataBit;
	BYTE stopBit;
	BYTE parity;

protected:
	/* Static */
	CStatic m_staticTerminal;
	CStatic m_staticMessage;

	/* Edit */
	CEdit m_editTerminal;
	CEdit m_editMessage;

	/* Button */
	CButton m_buttonConnect;
	CButton m_buttonDisconnect;
	CButton m_buttonSetup;
	CButton m_buttonLED;
	CButton m_buttonLED1;
	CButton m_buttonLED2;
	CButton m_buttonLED3;
	CButton m_buttonSend;

protected:
	
	afx_msg void OnPortOpen();
	afx_msg void OnPortClose();
	afx_msg void OnSendLED1();
	afx_msg void OnSendLED2();
	afx_msg void OnSendLED3();
	afx_msg void OnSendMessage();
	afx_msg LRESULT OnReceiveMessage(WPARAM wParam, LPARAM lParam);

protected:

public:
	HWND GetHWND();
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEdit m_eidt1;
	CRichEditCtrl rich_edit2;
	CString m_richedit_value;

	void TextOut(LPCTSTR strText, COLORREF TextColor);//RichEdit2.0 의 마지막 줄로 자동 이동, 색 변경

	afx_msg void OnCbnDropdownCombo1();
	void GetserialPort();

	CComboBox Con_Combobox1_for_Serial;
};
