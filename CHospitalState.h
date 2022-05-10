#pragma once
class CHospitalState
{
public:
	CString strCode;
	CString strName;
};
using CHospitalStatePtr = shared_ptr<CHospitalState>;

class CHospitalStateDAO
{
private:
	CDatabase& m_db;
public:
	CHospitalStateDAO(CDatabase& db) : m_db(db) {
	}

	vector<CHospitalStatePtr> GetListHospitalState();
	map<CString, CString> GetMapHospitalState();

};
