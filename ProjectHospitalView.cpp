
// ProjectHospitalView.cpp: CProjectHospitalView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ProjectHospital.h"
#endif

#include "ProjectHospitalDoc.h"
#include "ProjectHospitalView.h"
#include "CHospitalDialog.h"
#include "CHospitalFindDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectHospitalView

IMPLEMENT_DYNCREATE(CProjectHospitalView, CFormView)

BEGIN_MESSAGE_MAP(CProjectHospitalView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CProjectHospitalView::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CProjectHospitalView::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CProjectHospitalView::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CProjectHospitalView::OnBnClickedButtonFind)
END_MESSAGE_MAP()

// CProjectHospitalView 생성/소멸

CProjectHospitalView::CProjectHospitalView() noexcept
	: CFormView(IDD_PROJECTHOSPITAL_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BOOL bRet = m_db.OpenEx(_T("DSN=scott_db;uid=user1;PWD=passwd;"), 0);
	if (!bRet) {
		AfxMessageBox(_T("DB 연결 실패"));
	}
}

CProjectHospitalView::~CProjectHospitalView()
{
	if (m_db.IsOpen()) {
		m_db.Close();
	}
}

void CProjectHospitalView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOSPITAL, m_listView);
}

BOOL CProjectHospitalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CProjectHospitalView::SetHospitalView(int nRow, const CHospitalPtr pHospital)
{
	m_listView.SetItemText(nRow, 1, pHospital->strColDate);
	m_listView.SetItemText(nRow, 2, pHospital->strColState);
	m_listView.SetItemText(nRow, 3, pHospital->strColDetailCode);
	m_listView.SetItemText(nRow, 4, pHospital->strColDetailName);
	m_listView.SetItemText(nRow, 5, pHospital->strColPhone);
	m_listView.SetItemText(nRow, 6, pHospital->nColPost);
	m_listView.SetItemText(nRow, 7, pHospital->strColAddr);
	m_listView.SetItemText(nRow, 8, pHospital->strColRoadAddr);
	m_listView.SetItemText(nRow, 9, pHospital->nColRoadPost);
	m_listView.SetItemText(nRow, 10, pHospital->strColName);
	m_listView.SetItemText(nRow, 11, pHospital->strColCategory);
	m_listView.SetItemText(nRow, 12, pHospital->strColCategoryDetail);
	m_listView.SetItemText(nRow, 13, pHospital->nColNumOfPerson);
	m_listView.SetItemText(nRow, 14, pHospital->nColNumOfRoom);
	m_listView.SetItemText(nRow, 15, pHospital->nColNumOfBed);
	m_listView.SetItemText(nRow, 16, pHospital->strColTreatSubName);
}

void CProjectHospitalView::GetDBAllHospitalView(vector<CHospitalPtr> hospitalList)
{
	m_listView.DeleteAllItems();

	int nRow = 0;
	for (const auto& pHospital : hospitalList) {
		m_listView.InsertItem(nRow, pHospital->strHospitalNo, 0);
		SetHospitalView(nRow, pHospital);
		nRow++;
	}
}



void CProjectHospitalView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_imageList.Create(48, 48, ILC_COLOR32, 5, 5);
	m_imageListSmall.Create(16, 16, ILC_COLOR32, 5, 5);

	m_imageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_imageListSmall.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	m_listView.SetImageList(&m_imageList, LVSIL_NORMAL);
	m_listView.SetImageList(&m_imageListSmall, LVSIL_SMALL);

	//컬럼 정보 출력 
	m_listView.InsertColumn(0, _T("번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(1, _T("인허가일자"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(2, _T("영업상태명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(3, _T("상세영업상태코드"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(4, _T("상세영업상태명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(5, _T("소재지전화"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(6, _T("소재지우편번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(7, _T("소재지전체주소"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(8, _T("도로명전체주소"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(9, _T("도로명우편번호"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(10, _T("사업장명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(11, _T("업태구분명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(12, _T("의료기관종별명"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(13, _T("의료인수"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(14, _T("입원실수"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(15, _T("병상수"), LVCFMT_LEFT, 100);
	m_listView.InsertColumn(16, _T("진료과목내용명"), LVCFMT_LEFT, 300);

	DWORD dwExStyle = m_listView.GetExtendedStyle();
	m_listView.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CHospitalDAO hospitalDAO(m_db);
	GetDBAllHospitalView(hospitalDAO.GetListHospital());
}


// CProjectHospitalView 인쇄

BOOL CProjectHospitalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CProjectHospitalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CProjectHospitalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CProjectHospitalView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CProjectHospitalView 진단

#ifdef _DEBUG
void CProjectHospitalView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProjectHospitalView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CProjectHospitalDoc* CProjectHospitalView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectHospitalDoc)));
	return (CProjectHospitalDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjectHospitalView 메시지 처리기


//삭제 버튼
void CProjectHospitalView::OnBnClickedButtonDelete()
{
	if (IDYES != AfxMessageBox(_T("삭제하시겠습니까?"), MB_YESNO))
	{
		return;
	}

	const int nCount = m_listView.GetItemCount();
	CString strHospitalNo;
	CString strSQL;

	CString strInParam;
	CArray<int, int> arr;

	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			//삭제할 사원 번호를 얻는다
			strHospitalNo = m_listView.GetItemText(i, 0);

			strInParam += strHospitalNo + _T(",");

			//삭제할 사원의 위치를 배열에 추가
			arr.Add(i);
		}
	}

	try {
		if (!strInParam.IsEmpty()) {
			//(,) 삭제
			strInParam.Delete(strInParam.GetLength() - 1, 1);
			//SQL 삭제 구문을 생성한다 
			strSQL = _T("delete from 병원 where 번호 in (") + strInParam + _T(")");

			//트랜젝션
			m_db.BeginTrans();
			m_db.ExecuteSQL(strSQL);//DML 구문 (insert, delete ,update, merge)
			m_db.CommitTrans();
			//리스트에서 삭제 항목을 제거
			for (int i = 0; i < arr.GetSize(); i++) {
				//목록에서 제거한다 
				m_listView.DeleteItem(arr.GetAt(i));
			}
			AfxMessageBox(_T("삭제가 완료되었습니다."));
		}
	}
	catch (const CException* p) {
		//트랜젝션 복구 //DML
		m_db.Rollback();
		TCHAR szErr[500];
		p->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
	}
}

//수정 버튼
void CProjectHospitalView::OnBnClickedButtonChange()
{
	const int nCount = m_listView.GetItemCount();
	CString strHospitalNo;

	//선택된 사번을 얻는다
	int nRow;
	for (int i = nCount - 1; i >= 0; --i) {
		if (m_listView.GetCheck(i)) {
			//선택된 사원 번호를 얻는다
			strHospitalNo = m_listView.GetItemText(i, 0);
			nRow = i;
			break;
		}
	}
	if (strHospitalNo.IsEmpty()) {
		AfxMessageBox(_T("사원을 선택해 주세요"));
		return;
	}

	//상세코드, 상세영업상태명, 업태구분명, 의료기관정별명을 얻기 위해 병원 리스트를 전달
	CHospitalDAO hospitalDAO(m_db);
	vector<CHospitalPtr> hospitalList = hospitalDAO.GetListHospital();
	//진료과목명을 얻기 위해 병원진료과목 리스트를 전달
	CMedicalClassDAO medicalClassDAO(m_db);
	vector<CMedicalClassPtr> medicalclassList = medicalClassDAO.GetListMedicalClass();
	//영업상태명을 얻기 위해 병원영업상태 리스트를 전달
	CHospitalStateDAO hospitalStateDAO(m_db);
	vector<CHospitalStatePtr> hospitalStateList = hospitalStateDAO.GetListHospitalState();
	//선택한 병원을 전달
	CHospitalPtr pHospital = hospitalDAO.GetHospital(strHospitalNo);
	//해당병원의 진료과목내용명을 얻기위해 병원진료과목목록을 전달
	CHospitalDAO hospitalSubjectDAO(m_db);
	vector<CHospitalSubjectPtr> hospitalSubjectList = hospitalSubjectDAO.GetListHospitalSubject();
	//대화상자를 출력
	CHospitalDialog dlg(hospitalList, medicalclassList, hospitalStateList, pHospital, hospitalSubjectList, m_db);

	if (dlg.DoModal() == IDOK) {
		pHospital->strColDate = dlg.m_strColDate;
		pHospital->strColPhone = dlg.m_strColPhone;
		pHospital->strColAddr = dlg.m_strColAddr;
		pHospital->strColRoadAddr = dlg.m_strColRoadAddr;
		pHospital->strColName = dlg.m_strColName;
		pHospital->strColTreatSubName = dlg.m_strColSubject;

		pHospital->nColPost.Format(_T("%d"), dlg.m_nColPost);
		pHospital->nColRoadPost.Format(_T("%d"), dlg.m_nColRoadPost);
		pHospital->nColNumOfPerson.Format(_T("%d"), dlg.m_nColNumOfPerson);
		pHospital->nColNumOfRoom.Format(_T("%d"), dlg.m_nColNumOfRoom);
		pHospital->nColNumOfBed.Format(_T("%d"), dlg.m_nColNumOfBed);

		CHospitalDAO hospitalDAO(m_db);

		if (hospitalDAO.UpdateHospital(pHospital)) {
			pHospital->strColState = dlg.m_strColState;
			SetHospitalView(nRow, pHospital);
		}

		//목록 체크한거 db및 뷰에 적용
		hospitalDAO.DeleteAllTreatList(dlg.m_strHospitalNo);
		pHospital->strColTreatSubName = "";
		const int nCount = dlg.m_nCount;
		for (const int& pchecklist : dlg.checklist) {
			hospitalDAO.InsertTreatList(dlg.m_strHospitalNo, dlg.m_medicalclassList[pchecklist]->strCode);
			pHospital->strColTreatSubName = pHospital->strColTreatSubName + "," + dlg.m_medicalclassList[pchecklist]->strName;
		}
		pHospital->strColTreatSubName.Delete(0, 1);

		SetHospitalView(nRow, pHospital);

		AfxMessageBox(_T("수정이 완료되었습니다"));
	}
}

//등록 버튼
void CProjectHospitalView::OnBnClickedButtonInsert()
{
	CHospitalDAO hospitalDAO(m_db);
	vector<CHospitalPtr> hospitalList = hospitalDAO.GetListHospital();
	CMedicalClassDAO medicalClassDAO(m_db);
	vector<CMedicalClassPtr> medicalclassList = medicalClassDAO.GetListMedicalClass();
	CHospitalStateDAO hospitalStateDAO(m_db);
	vector<CHospitalStatePtr> hospitalStateList = hospitalStateDAO.GetListHospitalState();
	CHospitalDAO hospitalSubjectDAO(m_db);
	vector<CHospitalSubjectPtr> hospitalSubjectList = hospitalSubjectDAO.GetListHospitalSubject();
	CHospitalPtr pHospital = make_shared<CHospital>();
	CHospitalDialog dlg(hospitalList, medicalclassList, hospitalStateList, pHospital, hospitalSubjectList, m_db);

	int nRow;

	if (dlg.DoModal() == IDOK) {
		//SQL 삽입 
		pHospital->strHospitalNo = dlg.m_strHospitalNo;
		pHospital->strColDate = dlg.m_strColDate;
		pHospital->strColPhone = dlg.m_strColPhone;
		pHospital->strColAddr = dlg.m_strColAddr;
		pHospital->strColRoadAddr = dlg.m_strColRoadAddr;
		pHospital->strColName = dlg.m_strColName;

		pHospital->nColPost.Format(_T("%d"), dlg.m_nColPost);
		pHospital->nColRoadPost.Format(_T("%d"), dlg.m_nColRoadPost);
		pHospital->nColNumOfPerson.Format(_T("%d"), dlg.m_nColNumOfPerson);
		pHospital->nColNumOfRoom.Format(_T("%d"), dlg.m_nColNumOfRoom);
		pHospital->nColNumOfBed.Format(_T("%d"), dlg.m_nColNumOfBed);

		CHospitalDAO hospitalDAO(m_db);
		if (hospitalDAO.InsertHospital(pHospital)) {
			nRow = m_listView.GetItemCount();
			m_listView.InsertItem(nRow, pHospital->strHospitalNo, 0);

			SetHospitalView(nRow, pHospital);
		}

		hospitalDAO.DeleteAllTreatList(dlg.m_strHospitalNo);
		pHospital->strColTreatSubName = "";
		const int nCount = dlg.m_nCount;
		for (const int& pchecklist : dlg.checklist) {
			hospitalDAO.InsertTreatList(dlg.m_strHospitalNo, dlg.m_medicalclassList[pchecklist]->strCode);
			pHospital->strColTreatSubName = pHospital->strColTreatSubName + "," + dlg.m_medicalclassList[pchecklist]->strName;
		}
		pHospital->strColTreatSubName.Delete(0, 1);

		pHospital->strColState = dlg.m_strColState;
		SetHospitalView(nRow, pHospital);

		AfxMessageBox(_T("등록이 완료되었습니다"));
	}
}

//검색 버튼
void CProjectHospitalView::OnBnClickedButtonFind()
{
	CHospitalFindDlg dlg;
	if (dlg.DoModal() == IDOK) {
		CHospitalDAO hospitalDAO(m_db);
		GetDBAllHospitalView(hospitalDAO.GetListHospitalFind(dlg.m_strHospitalName, dlg.m_strHospitalPhone));
	}
}
