#pragma once
//진료과목 
class CMedicalClass
{
public:
	CString strCode;
	CString strName;
};
using CMedicalClassPtr = shared_ptr<CMedicalClass>;

class CMedicalClassDAO
{
private:
	CDatabase& m_db;
public:
	CMedicalClassDAO(CDatabase& db) : m_db(db) {
	}

	vector<CMedicalClassPtr> GetListMedicalClass();

};

