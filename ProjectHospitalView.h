
// ProjectHospitalView.h: CProjectHospitalView 클래스의 인터페이스
//

#pragma once
#include "CHospital.h"
#include "CMedicalClass.h"
#include "ProjectHospitalDoc.h"

class CProjectHospitalView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CProjectHospitalView() noexcept;
	DECLARE_DYNCREATE(CProjectHospitalView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_PROJECTHOSPITAL_FORM };
#endif

// 특성입니다.
public:
	CProjectHospitalDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CProjectHospitalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	//DB 연결 
	CDatabase m_db;

	CListCtrl m_listView;
	CImageList  m_imageList;
	CImageList 	m_imageListSmall;

	void SetHospitalView(int nRow, const CHospitalPtr pHospital);
	void GetDBAllHospitalView(vector<CHospitalPtr> hospitalList);

	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonFind();
};

#ifndef _DEBUG  // ProjectHospitalView.cpp의 디버그 버전
inline CProjectHospitalDoc* CProjectHospitalView::GetDocument() const
   { return reinterpret_cast<CProjectHospitalDoc*>(m_pDocument); }
#endif

