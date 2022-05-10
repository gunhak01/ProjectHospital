// CHospitalFindDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ProjectHospital.h"
#include "CHospitalFindDlg.h"
#include "afxdialogex.h"


// CHospitalFindDlg 대화 상자

IMPLEMENT_DYNAMIC(CHospitalFindDlg, CDialogEx)

CHospitalFindDlg::CHospitalFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_FIND, pParent)
	, m_strHospitalName(_T(""))
	, m_strHospitalPhone(_T(""))
{

}

CHospitalFindDlg::~CHospitalFindDlg()
{
}

void CHospitalFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIND_NAME, m_strHospitalName);
	DDX_Text(pDX, IDC_EDIT_FIND_PHONE, m_strHospitalPhone);
}


BEGIN_MESSAGE_MAP(CHospitalFindDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHospitalFindDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHospitalFindDlg 메시지 처리기


void CHospitalFindDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_strHospitalName.IsEmpty() && m_strHospitalPhone.IsEmpty()) {
		AfxMessageBox(_T("병원명 또는 전화번호를 입력해주세요"));
		GetDlgItem(IDC_EDIT_FIND_NAME)->SetFocus();
		return;
	}
	CDialogEx::OnOK();
}
