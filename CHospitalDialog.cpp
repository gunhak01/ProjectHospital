// CHospitalDialog.cpp: 구현 파일
//
#include "pch.h"
#include "ProjectHospital.h"
#include "CHospitalDialog.h"
#include "afxdialogex.h"

// CHospitalDialog 대화 상자

IMPLEMENT_DYNAMIC(CHospitalDialog, CDialogEx)

CHospitalDialog::CHospitalDialog(vector<CHospitalPtr>& hospitalList, vector<CMedicalClassPtr>& medicalclassList, vector<CHospitalStatePtr>& hospitalStateList, CHospitalPtr pHospital, vector<CHospitalSubjectPtr>& hospitalSubjectList, CDatabase& db, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSPITAL_UPDATE, pParent)
	, m_hospitalList(hospitalList)
	, m_medicalclassList(medicalclassList)
	, m_hospitalStateList(hospitalStateList)
	, m_pHospital(pHospital)
	, m_hospitalSubjectList(hospitalSubjectList)
	, m_db(db)
	, m_strHospitalNo(_T(""))
	, m_strColDate(_T(""))
	, m_strColPhone(_T(""))
	, m_nColPost(0)
	, m_strColAddr(_T(""))
	, m_strColRoadAddr(_T(""))
	, m_nColRoadPost(0)
	, m_strColName(_T(""))
	, m_nColNumOfPerson(0)
	, m_nColNumOfRoom(0)
	, m_nColNumOfBed(0)
	, m_strColState(_T(""))
	, m_strColDetailCode(_T(""))
	, m_strColDetailName(_T(""))
	, m_strColCategory(_T(""))
	, m_strColCategoryDetail(_T(""))
	, m_strColSubject(_T(""))
{

}

CHospitalDialog::~CHospitalDialog()
{
}

void CHospitalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NO, m_strHospitalNo);
	DDX_Text(pDX, IDC_EDIT_DATE, m_strColDate);
	DDX_Control(pDX, IDC_COMBO_STATE, m_comboColState);
	DDX_Control(pDX, IDC_COMBO_DETAIL_CODE, m_comboColDetailCode);
	DDX_Control(pDX, IDC_COMBO_DETAIL_NAME, m_comboColDetailName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strColPhone);
	DDX_Text(pDX, IDC_EDIT_POST, m_nColPost);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_strColAddr);
	DDX_Text(pDX, IDC_EDIT_ROAD_ADDR, m_strColRoadAddr);
	DDX_Text(pDX, IDC_EDIT_ROAD_POST, m_nColRoadPost);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strColName);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_comboColCategory);
	DDX_Control(pDX, IDC_COMBO_CATEGORY_DETAIL, m_comboColCategoryDetail);
	DDX_Text(pDX, IDC_EDIT_NUM_OF_PERSON, m_nColNumOfPerson);
	DDX_Text(pDX, IDC_EDIT_NUM_OF_ROOM, m_nColNumOfRoom);
	DDX_Text(pDX, IDC_EDIT_NUM_OF_BED, m_nColNumOfBed);
	DDX_CBString(pDX, IDC_COMBO_STATE, m_strColState);
	DDX_CBString(pDX, IDC_COMBO_DETAIL_CODE, m_strColDetailCode);
	DDX_CBString(pDX, IDC_COMBO_DETAIL_NAME, m_strColDetailName);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_strColCategory);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY_DETAIL, m_strColCategoryDetail);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_strColSubject);
	DDX_Control(pDX, IDC_LIST_TREAT_SUBJECT, m_treatlistView);
}


BEGIN_MESSAGE_MAP(CHospitalDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OVERLAP, &CHospitalDialog::OnBnClickedButtonOverlap)
	ON_CBN_SELENDOK(IDC_COMBO_STATE, &CHospitalDialog::OnCbnSelendokComboState)
	ON_CBN_SELENDOK(IDC_COMBO_DETAIL_CODE, &CHospitalDialog::OnCbnSelendokComboDetailCode)
	ON_CBN_SELENDOK(IDC_COMBO_DETAIL_NAME, &CHospitalDialog::OnCbnSelendokComboDetailName)
	ON_CBN_SELENDOK(IDC_COMBO_CATEGORY, &CHospitalDialog::OnCbnSelendokComboCategory)
	ON_CBN_SELENDOK(IDC_COMBO_CATEGORY_DETAIL, &CHospitalDialog::OnCbnSelendokComboCategoryDetail)
END_MESSAGE_MAP()


// CHospitalDialog 메시지 처리기

void CHospitalDialog::GetDBAllMedicdalView(vector<CMedicalClassPtr> medicalClassList)
{
	m_treatlistView.DeleteAllItems();

	int nRow = 0;
	for (const auto& pMedicalClass : medicalClassList) {
		m_treatlistView.InsertItem(nRow, pMedicalClass->strCode, 0);
		m_treatlistView.SetItemText(nRow, 1, pMedicalClass->strName);

		nRow++;
	}
}



BOOL CHospitalDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_pHospital->strHospitalNo.IsEmpty()) {
		((CEdit*)GetDlgItem(IDC_EDIT_NO))->SetReadOnly(FALSE);
		GetDlgItem(IDC_BUTTON_OVERLAP)->ShowWindow(SW_SHOW);
	}

	m_treatlistView.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 100);
	m_treatlistView.InsertColumn(1, _T("진료과목코드"), LVCFMT_LEFT, 100);

	DWORD dwExStyle = m_treatlistView.GetExtendedStyle();
	m_treatlistView.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CMedicalClassDAO medicalClassDAO(m_db);
	GetDBAllMedicdalView(medicalClassDAO.GetListMedicalClass());

	m_strHospitalNo = m_pHospital->strHospitalNo;
	m_strColDate = m_pHospital->strColDate;
	m_strColPhone = m_pHospital->strColPhone;
	m_nColPost = _ttoi(m_pHospital->nColPost.GetBuffer());
	m_strColAddr = m_pHospital->strColAddr;
	m_strColRoadAddr = m_pHospital->strColRoadAddr;
	m_nColRoadPost = _ttoi(m_pHospital->nColRoadPost.GetBuffer());
	m_strColName = m_pHospital->strColName;
	m_nColNumOfPerson = _ttoi(m_pHospital->nColNumOfPerson.GetBuffer());
	m_nColNumOfRoom = _ttoi(m_pHospital->nColNumOfRoom.GetBuffer());
	m_nColNumOfBed = _ttoi(m_pHospital->nColNumOfBed.GetBuffer());

	m_strColState = m_pHospital->strColState;
	m_strColDetailCode = m_pHospital->strColDetailCode;
	m_strColDetailName = m_pHospital->strColDetailName;
	m_strColCategory = m_pHospital->strColCategory;
	m_strColCategoryDetail = m_pHospital->strColCategoryDetail;
	m_strColSubject = m_pHospital->strColTreatSubName;

	vector<CString> arr;

	LPTSTR lpszCol16 = m_pHospital->strColTreatSubName.GetBuffer();
	LPTSTR lpszToken = NULL;
	LPTSTR lpszNextToken = NULL;
	lpszToken = _tcstok_s(lpszCol16, _T(","), &lpszNextToken);
	while (lpszToken) {
		arr.push_back(lpszToken);
		lpszToken = _tcstok_s(NULL, _T(","), &lpszNextToken);
	}

	const int nCount = m_treatlistView.GetItemCount();
	m_nCount = m_treatlistView.GetItemCount();

	for (const auto& parr : arr) {
		for (int i = 0; i < nCount; i++) {
			if (parr == m_medicalclassList[i]->strCode) {
				m_treatlistView.SetCheck(i);
			}
		}
	}

	int nIndex = 0;
	for (const auto& pCHospitalState : m_hospitalStateList) {
		m_comboColState.InsertString(nIndex++, pCHospitalState->strName);
	}
	nIndex = 0;
	for (const auto& pCHospital : m_hospitalList) {
		int index = m_comboColDetailCode.FindStringExact(-1, pCHospital->strColDetailCode);
		if (index == LB_ERR) {
			m_comboColDetailCode.InsertString(nIndex++, pCHospital->strColDetailCode);
			arrDetailCode.push_back(pCHospital->strColDetailCode);
		}
	}
	nIndex = 0;
	for (const auto& pCHospital : m_hospitalList) {
		int index = m_comboColDetailName.FindStringExact(-1, pCHospital->strColDetailName);
		if (index == LB_ERR) {
			m_comboColDetailName.InsertString(nIndex++, pCHospital->strColDetailName);
			arrDetailName.push_back(pCHospital->strColDetailName);
		}
	}
	nIndex = 0;
	for (const auto& pCHospital : m_hospitalList) {
		int index = m_comboColCategory.FindStringExact(-1, pCHospital->strColCategory);
		if (index == LB_ERR) {
			m_comboColCategory.InsertString(nIndex++, pCHospital->strColCategory);
			arrCategory.push_back(pCHospital->strColCategory);
		}
	}
	nIndex = 0;
	for (const auto& pCHospital : m_hospitalList) {
		int index = m_comboColCategoryDetail.FindStringExact(-1, pCHospital->strColCategoryDetail);
		if (index == LB_ERR && pCHospital->strColCategoryDetail != "") {
			m_comboColCategoryDetail.InsertString(nIndex++, pCHospital->strColCategoryDetail);
			//AfxMessageBox(pCHospital->strColCategoryDetail);
			arrCategoryDetail.push_back(pCHospital->strColCategoryDetail);
		}
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHospitalDialog::OnBnClickedButtonOverlap()
{
	//사번을 읽어들인다.
	GetDlgItemText(IDC_EDIT_NO, m_strHospitalNo);
	if (m_strHospitalNo.IsEmpty()) {
		AfxMessageBox(_T("사번을 입력해주세요"));
		GetDlgItem(IDC_EDIT_NO)->SetFocus();
		return;
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CProjectHospitalView* pView = (CProjectHospitalView*)pMainFrame->GetActiveView();

	CHospitalDAO hospitalDAO(pView->m_db);
	CHospitalPtr pHospital = hospitalDAO.GetHospital(m_strHospitalNo);
	if (pHospital->strHospitalNo == m_strHospitalNo) {
		AfxMessageBox(m_strHospitalNo + _T(" 사번은 중복 되었습니다"));
		SetDlgItemText(IDC_EDIT_NO, _T(""));
		GetDlgItem(IDC_EDIT_NO)->SetFocus();
		return;
	}
	else {
		AfxMessageBox(_T("사용하실 수 있습니다"));
	}
}


void CHospitalDialog::OnCbnSelendokComboState()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_comboColState.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		const CHospitalStatePtr pHospitalState = m_hospitalStateList[nCurSel];
		m_strColState = pHospitalState->strCode;
	}
}


void CHospitalDialog::OnCbnSelendokComboDetailCode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_comboColDetailCode.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		m_pHospital->strColDetailCode = arrDetailCode[nCurSel];
	}
}


void CHospitalDialog::OnCbnSelendokComboDetailName()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_comboColDetailName.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		m_pHospital->strColDetailName = arrDetailName[nCurSel];
	}
}


void CHospitalDialog::OnCbnSelendokComboCategory()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_comboColCategory.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		m_pHospital->strColCategory = arrCategory[nCurSel];
	}
}


void CHospitalDialog::OnCbnSelendokComboCategoryDetail()
{
	int nCurSel = m_comboColCategoryDetail.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		m_pHospital->strColCategoryDetail = arrCategoryDetail[nCurSel];
	}
}

void CHospitalDialog::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	for (int i = m_nCount - 1; i >= 0; --i) {
		if (m_treatlistView.GetCheck(i)) {
			checklist.push_back(i);
		}
	}

	int nCurSel = m_comboColState.GetCurSel();
	if (nCurSel >= 0 && nCurSel < m_hospitalStateList.size()) {
		const CHospitalStatePtr pHospitalState = m_hospitalStateList[nCurSel];
		m_pHospital->strColState = pHospitalState->strCode;
	}

	CDialogEx::OnOK();
}
