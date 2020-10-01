
// Serial_Testing_projectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Serial_Testing_project.h"
#include "Serial_Testing_projectDlg.h"
#include "afxdialogex.h"

HWND hCommWnd;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSerialTestingprojectDlg 대화 상자

CSerialTestingprojectDlg::CSerialTestingprojectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERIAL_TESTING_PROJECT_DIALOG, pParent)
	, m_richedit_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialTestingprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_eidt1);
	DDX_Control(pDX, IDC_RICHEDIT21, rich_edit2);
	DDX_Text(pDX, IDC_RICHEDIT21, m_richedit_value);
	DDX_Control(pDX, IDC_COMBO1, Con_Combobox1_for_Serial);
}


BEGIN_MESSAGE_MAP(CSerialTestingprojectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_READ, OnReceiveMessage)
	ON_BN_CLICKED(IDC_BUTTON1, &CSerialTestingprojectDlg::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_CBN_DROPDOWN(IDC_COMBO1, &CSerialTestingprojectDlg::OnCbnDropdownCombo1)
//	ON_CBN_SELCHANGE(IDC_COMBO1, &CSerialTestingprojectDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CSerialTestingprojectDlg 메시지 처리기

BOOL CSerialTestingprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialTestingprojectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSerialTestingprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
// 메시지 핸들러 함수
/************************************************************************/
/* OnCreate - ON_WM_CREATE */
/************************************************************************/

int CSerialTestingprojectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	hCommWnd = this->m_hWnd;

	return 0;
}
/************************************************************************/
/* Combobox_1 내릴 경우 작동 */
/************************************************************************/
void CSerialTestingprojectDlg::OnCbnDropdownCombo1()
{ 
	GetserialPort();
}

void CSerialTestingprojectDlg::GetserialPort()
{
	HKEY hKey;

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);
	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	Con_Combobox1_for_Serial.ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));

	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{

		index++;
		//szName-> 레지스터 항목의 이름
		//dwType-> 항목의 타입, 여기에서는널로 끝나는 문자열
		//szData-> 항목값이 저장될 배열
		//dwSize2-> 배열의 크기
		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		Con_Combobox1_for_Serial.AddString((CString)szData);

		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));

		dwSize = 100;
		dwSize2 = 20;				
	}
	RegCloseKey(hKey);
}

/************************************************************************/
/* OnPortOpen afx_msg */
/************************************************************************/
void CSerialTestingprojectDlg::OnPortOpen()
{	
	Con_Combobox1_for_Serial.GetLBText(Con_Combobox1_for_Serial.GetCurSel(),serialPort);//combobox 에 있는 몇번째 아이템(getCurSel) 의 값을 SerialPort(CString 형) 에 저장
	//this->serialPort = "COM3";
	//GetDlgItemText(IDC_COMBO1,serialPort);
	
	this->baudRate = (DWORD)CBR_115200;
	this->dataBit = (BYTE)8;
	this->stopBit = (BYTE)ONESTOPBIT;
	this->parity = (BYTE)NOPARITY;

	if (this->cComThread.m_bConnected == FALSE) { /* 포트가 닫혀 있을 경우에만 포트를 연다 */
		this->cComThread.OpenPort(this->serialPort, this->baudRate, this->dataBit,
			this->stopBit, this->parity);

		//AfxMessageBox("Port Connection Success");
	}
	else if (this->cComThread.m_bConnected == TRUE) {
		//AfxMessageBox("Already Port Connection");
	}
}

/************************************************************************/
/* OnPortClose - afx_msg */
/************************************************************************/
void CSerialTestingprojectDlg::OnPortClose()
{
	if (this->cComThread.m_bConnected == TRUE) {
		this->cComThread.ClosePort();

		AfxMessageBox("Port Disconnection Success");
	}
	else if (this->cComThread.m_bConnected == FALSE) {
		AfxMessageBox("Already Port Disconnection");
	}
}

//////////////////////////////////////////////////////////////////////////
// 아스키 값 전송 하기
/************************************************************************/
/* OnSendLED1 - afx_msg */
/************************************************************************/
void CSerialTestingprojectDlg::OnSendLED1()
{
	BYTE sendData;

	sendData = '1';

	this->cComThread.WriteComm(&sendData, 1);
}

/************************************************************************/
/* OnSendLED2 - afx_msg */
/************************************************************************/
void CSerialTestingprojectDlg::OnSendLED2()
{
	BYTE sendData;

	sendData = '2';

	this->cComThread.WriteComm(&sendData, 1);
}

/************************************************************************/
/* OnSendLED3 - afx_msg */
/************************************************************************/
void CSerialTestingprojectDlg::OnSendLED3()
{
	BYTE sendData;

	sendData = '3';

	this->cComThread.WriteComm(&sendData, 1);
}

/************************************************************************/
/* OnSendMessage */
/************************************************************************/
void CSerialTestingprojectDlg::OnSendMessage()
{
	this->m_editMessage.SetWindowText("");
}

/************************************************************************/
/* OnReceiveMessage */
/************************************************************************/
LRESULT CSerialTestingprojectDlg::OnReceiveMessage(WPARAM wParam, LPARAM lParam)
{
	BYTE buffer;
	CString message;
	int length = -1;
	length = this->cComThread.m_QueueRead.GetSize();

	for (int i = 0; i < length; i++) {
		this->cComThread.m_QueueRead.GetByte(&buffer);

		message += buffer;
	}

	//SetDlgItemText(IDC_EDIT1, message);
	
	this->m_eidt1.SetSel(-1, 0);
	//this->m_eidt1.ReplaceSel(message);
	if (message != "\n")
	TextOut(message, RGB(0, 0, 255)); // 파란색으로 richedit2.0, 마지막줄로 자동 이동 Log 활용

	return 0;
}
void CSerialTestingprojectDlg::TextOut(LPCTSTR strText, COLORREF TextColor)
{

	// 마지막 행으로 이동하기
	int first_pos = rich_edit2.LineIndex(rich_edit2.GetLineCount());
	rich_edit2.SetSel(first_pos, first_pos);
	CPoint point;
	point = rich_edit2.PosFromChar(first_pos);
	rich_edit2.SetCaretPos(point);
	rich_edit2.SetFocus();

	// 문자출력
	CHARFORMAT cf;
	memset(&cf, 0, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = TextColor;

	rich_edit2.SetSelectionCharFormat(cf);
	rich_edit2.ReplaceSel(strText);
}

void CSerialTestingprojectDlg::OnBnClickedButton1()
{
	CString Button_caption;
	GetDlgItemText(IDC_BUTTON1, Button_caption);
	if (Button_caption== "Connect")
	{
		OnPortOpen();
		SetDlgItemText(IDC_BUTTON1, "Disconnect");
	}
	else
	{
		OnPortClose();
		SetDlgItemText(IDC_BUTTON1, "Connect");
	}
}

