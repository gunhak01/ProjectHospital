#include "pch.h"
#include "CHospitalState.h"

vector<CHospitalStatePtr> CHospitalStateDAO::GetListHospitalState()
{
	vector<CHospitalStatePtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select * from 병원영업상태"));

	while (!rs.IsEOF()) {
		CHospitalStatePtr pHospitalState = make_shared<CHospitalState>(); //new CHospitalState;
		if (pHospitalState == nullptr) return vector<CHospitalStatePtr>();

		rs.GetFieldValue((short)0, pHospitalState->strCode);
		rs.GetFieldValue((short)1, pHospitalState->strName);

		rs.MoveNext();

		resultList.push_back(pHospitalState);
	}
	rs.Close();


	return resultList;
}

map<CString, CString> CHospitalStateDAO::GetMapHospitalState()
{
	map<CString, CString> resultMap;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select * from 병원영업상태"));

	CString strCode;
	CString strName;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, strCode);
		rs.GetFieldValue((short)1, strName);

		rs.MoveNext();

		resultMap[strName] = strCode;
	}
	rs.Close();

	return resultMap;
}
