#pragma once
//병원 
class CHospital
{
public:
	CString strHospitalNo;
	CString strColDate;
	CString strColState;
	CString strColDetailCode;
	CString strColDetailName;
	CString strColPhone;
	CString nColPost;
	CString strColAddr;
	CString strColRoadAddr;
	CString nColRoadPost;
	CString strColName;
	CString strColCategory;
	CString strColCategoryDetail;
	CString nColNumOfPerson;
	CString nColNumOfRoom;
	CString nColNumOfBed;
	CString strColTreatSubName; //진료과목내용명 
	CString strColTreatSubCode; //진료과목코드

};
using CHospitalPtr = shared_ptr<CHospital>;

class CHospitalSubject
{
public:
	CString strSubjectCode;
	CString strSubjectName;

};
using CHospitalSubjectPtr = shared_ptr<CHospitalSubject>;

class CHospitalDAO {
private:
	CDatabase& m_db;
public:
	CHospitalDAO(CDatabase& db) : m_db(db) {}

	vector<CHospitalPtr> GetListHospital();
	CHospitalPtr GetHospital(CString strHospitalNo);
	BOOL UpdateHospital(CHospitalPtr pEmp);
	BOOL InsertHospital(CHospitalPtr pHospital);
	vector<CHospitalPtr> GetListHospitalFind(CString strHospitalName, CString strHospitalPhone);

	vector<CHospitalSubjectPtr> GetListHospitalSubject();
	BOOL InsertTreatList(CString strHospitalNo, CString pstrState);
	BOOL DeleteTreatList(CString strHospitalNo, CString pstrState);
	BOOL DeleteAllTreatList(CString strHospitalNo);
};