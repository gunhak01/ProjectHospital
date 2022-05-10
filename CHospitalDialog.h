#pragma once


// CHospitalDialog 대화 상자
#include "CHospital.h"
#include "CMedicalClass.h"
#include "CHospitalState.h"
#include "MainFrm.h"
#include "ProjectHospitalView.h"

class CHospitalDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHospitalDialog)

public:
	CHospitalDialog(vector<CHospitalPtr>& hospitalList, vector<CMedicalClassPtr>& medicalclassList, vector<CHospitalStatePtr>& hospitalStateList, CHospitalPtr pHospital, vector<CHospitalSubjectPtr>& hospitalSubjectList, CDatabase& db, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHospitalDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITAL_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	vector<CHospitalPtr>& m_hospitalList;
	vector<CMedicalClassPtr>& m_medicalclassList;
	vector<CHospitalStatePtr>& m_hospitalStateList;
	CHospitalPtr m_pHospital;
	vector<CHospitalSubjectPtr>& m_hospitalSubjectList;

	vector<CString> arrDetailCode;
	vector<CString> arrDetailName;
	vector<CString> arrCategory;
	vector<CString> arrCategoryDetail;

	CString m_strHospitalNo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOverlap();
	CString m_strColDate;
	CComboBox m_comboColState;
	CComboBox m_comboColDetailCode;
	CComboBox m_comboColDetailName;
	CString m_strColPhone;
	int m_nColPost;
	CString m_strColAddr;
	CString m_strColRoadAddr;
	int m_nColRoadPost;
	CString m_strColName;
	CComboBox m_comboColCategory;
	CComboBox m_comboColCategoryDetail;
	int m_nColNumOfPerson;
	int m_nColNumOfRoom;
	int m_nColNumOfBed;
	CString m_strColState;
	CString m_strColDetailCode;
	CString m_strColDetailName;
	CString m_strColCategory;
	CString m_strColCategoryDetail;
	CString m_strColSubject;
	afx_msg void OnCbnSelendokComboState();
	afx_msg void OnCbnSelendokComboDetailCode();
	afx_msg void OnCbnSelendokComboDetailName();
	afx_msg void OnCbnSelendokComboCategory();
	afx_msg void OnCbnSelendokComboCategoryDetail();

	CListCtrl m_treatlistView;

	CDatabase& m_db;
	void SetMedicalView(int nRow, const CMedicalClassPtr pMedicalClass);
	void GetDBAllMedicdalView(vector<CMedicalClassPtr> medicalClassList);

	int m_nCount;
	vector<int> checklist;

	virtual void OnOK();
};
