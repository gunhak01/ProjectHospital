#include "pch.h"
#include "CMedicalClass.h"

vector<CMedicalClassPtr> CMedicalClassDAO::GetListMedicalClass()
{
	vector<CMedicalClassPtr> resultList;

	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select * from 병원진료과목"));

	while (!rs.IsEOF()) {
		CMedicalClassPtr pMedicalClass = make_shared<CMedicalClass>(); //new CMedicalClass;
		if (pMedicalClass == nullptr) return vector<CMedicalClassPtr>();

		rs.GetFieldValue((short)0, pMedicalClass->strCode);
		rs.GetFieldValue((short)1, pMedicalClass->strName);

		rs.MoveNext();

		resultList.push_back(pMedicalClass);
	}
	rs.Close();

	return resultList;
}