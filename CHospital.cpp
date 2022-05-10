#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	//SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select\
		a.��ȣ, a.���㰡����, d.�������¸�, a.�󼼿��������ڵ�, a.�󼼿������¸�, a.��������ȭ,\
		a.�����������ȣ, a.��������ü�ּ�, a.���θ���ü�ּ�, a.���θ�����ȣ, a.������, a.���±��и�,\
		a.�Ƿ���������, a.�Ƿ��μ�, a.�Կ��Ǽ�, a.�����\
		,listagg(c.��������, ',')\
		,listagg(b.��������ڵ�, ',')\
		from ���� a, ������������� b, ����������� c, ������������ d\
		where  a.��ȣ = b.��ȣ\
		and a.�������¸� = d.�������°�\
		and c.��������ڵ� = b.��������ڵ�\
		group by a.��ȣ, a.���㰡����, d.�������¸�, a.�󼼿��������ڵ�, a.�󼼿������¸�, a.��������ȭ,\
		a.�����������ȣ, a.��������ü�ּ�, a.���θ���ü�ּ�, a.���θ�����ȣ, a.������, a.���±��и�,\
		a.�Ƿ���������, a.�Ƿ��μ�, a.�Կ��Ǽ�, a.�����;"));

	//SQL ���� ���� ��� ��� 
	while (!rs.IsEOF()) {
		//����Ʈ �����͸� �̿��Ͽ� ��ü ������
		CHospitalPtr pHospital = make_shared<CHospital>(); //new CHospital;
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		//DB���� ��ȸ�� Hospital 1���� pHospital ��ü�� �����ϴ� �κ�  
		rs.GetFieldValue(_T("��ȣ"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("���㰡����"), pHospital->strColDate);
		rs.GetFieldValue((short)2, pHospital->strColState);
		rs.GetFieldValue((short)3, pHospital->strColDetailCode);
		rs.GetFieldValue((short)4, pHospital->strColDetailName);
		rs.GetFieldValue((short)5, pHospital->strColPhone);
		rs.GetFieldValue((short)6, pHospital->nColPost);
		rs.GetFieldValue((short)7, pHospital->strColAddr);
		rs.GetFieldValue((short)8, pHospital->strColRoadAddr);
		rs.GetFieldValue((short)9, pHospital->nColRoadPost);
		rs.GetFieldValue((short)10, pHospital->strColName);
		rs.GetFieldValue((short)11, pHospital->strColCategory);
		rs.GetFieldValue((short)12, pHospital->strColCategoryDetail);
		rs.GetFieldValue((short)13, pHospital->nColNumOfPerson);
		rs.GetFieldValue((short)14, pHospital->nColNumOfRoom);
		rs.GetFieldValue((short)15, pHospital->nColNumOfBed);
		rs.GetFieldValue((short)16, pHospital->strColTreatSubName);
		rs.GetFieldValue((short)17, pHospital->strColTreatSubCode);

		rs.MoveNext();

		//�迭�� ����Ʈ ������ ��ü(pHospital)�� �߰��Ѵ� 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

CHospitalPtr CHospitalDAO::GetHospital(CString strHospitalNo)
{
	//����Ʈ �����͸� �̿��Ͽ� ��ü������
	CHospitalPtr pHospital = make_shared<CHospital>();

	//SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select\
		a.��ȣ, ���㰡����, b.�������¸�, �󼼿��������ڵ�, �󼼿������¸�, ��������ȭ,\
		�����������ȣ, ��������ü�ּ�, ���θ���ü�ּ�, ���θ�����ȣ, ������, ���±��и�,\
		�Ƿ���������, �Ƿ��μ�, �Կ��Ǽ�, �����, c.��������ڵ�\
		from ���� a, ������������ b,\
		(select e.��ȣ, LISTAGG(g.��������ڵ�, ',') ��������ڵ�\
		from ���� e, ������������ f, ������������� g\
		where e.�������¸� = f.�������°�\
		and g.��ȣ = e.��ȣ\
		group by e.��ȣ) c\
		where a.�������¸� = b.�������°�\
		and c.��ȣ = a.��ȣ\
		and a.��ȣ = ") + strHospitalNo);

	//SQL ���� ���� ��� ��� 
	if (!rs.IsEOF()) {

		rs.GetFieldValue((short)0, pHospital->strHospitalNo);
		rs.GetFieldValue((short)1, pHospital->strColDate);
		rs.GetFieldValue((short)2, pHospital->strColState);
		rs.GetFieldValue((short)3, pHospital->strColDetailCode);
		rs.GetFieldValue((short)4, pHospital->strColDetailName);
		rs.GetFieldValue((short)5, pHospital->strColPhone);
		rs.GetFieldValue((short)6, pHospital->nColPost);
		rs.GetFieldValue((short)7, pHospital->strColAddr);
		rs.GetFieldValue((short)8, pHospital->strColRoadAddr);
		rs.GetFieldValue((short)9, pHospital->nColRoadPost);
		rs.GetFieldValue((short)10, pHospital->strColName);
		rs.GetFieldValue((short)11, pHospital->strColCategory);
		rs.GetFieldValue((short)12, pHospital->strColCategoryDetail);
		rs.GetFieldValue((short)13, pHospital->nColNumOfPerson);
		rs.GetFieldValue((short)14, pHospital->nColNumOfRoom);
		rs.GetFieldValue((short)15, pHospital->nColNumOfBed);
		rs.GetFieldValue((short)16, pHospital->strColTreatSubName);
	}
	rs.Close();

	return pHospital;
}

BOOL CHospitalDAO::UpdateHospital(CHospitalPtr pHospital)
{
	//������ SQL ���� ����
	CString strSQL;
	
	strSQL.Format(_T("update ���� set \
		���㰡����='%s', �������¸�='%s', �󼼿��������ڵ�='%s', �󼼿������¸� ='%s', ��������ȭ='%s', \
		�����������ȣ='%s', ��������ü�ּ�='%s', ���θ���ü�ּ�='%s', ���θ�����ȣ='%s', ������='%s', \
		���±��и�='%s', �Ƿ���������='%s', �Ƿ��μ�='%s', �Կ��Ǽ�='%s', �����='%s' \
		where ��ȣ='%s'"),
		pHospital->strColDate.GetBuffer(),
		pHospital->strColState.GetBuffer(),
		pHospital->strColDetailCode.GetBuffer(),
		pHospital->strColDetailName.GetBuffer(),
		pHospital->strColPhone.GetBuffer(),
		pHospital->nColPost.GetBuffer(),
		pHospital->strColAddr.GetBuffer(),
		pHospital->strColRoadAddr.GetBuffer(),
		pHospital->nColRoadPost.GetBuffer(),
		pHospital->strColName.GetBuffer(),
		pHospital->strColCategory.GetBuffer(),
		pHospital->strColCategoryDetail.GetBuffer(),
		pHospital->nColNumOfPerson.GetBuffer(),
		pHospital->nColNumOfRoom.GetBuffer(),
		pHospital->nColNumOfBed.GetBuffer(),
		pHospital->strHospitalNo.GetBuffer());

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}
	return TRUE;
}

BOOL CHospitalDAO::InsertHospital(CHospitalPtr pHospital)
{
	//����� SQL ���� ����
	CString strSQL;
	strSQL.Format(_T("insert into ���� (\
		��ȣ, ���㰡����, �������¸�, �󼼿��������ڵ�, �󼼿������¸�, ��������ȭ, \
		�����������ȣ, ��������ü�ּ�, ���θ���ü�ּ�, ���θ�����ȣ, ������, ���±��и�, \
		�Ƿ���������, �Ƿ��μ�, �Կ��Ǽ�, \
		�����) values (\
		'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')"),
		pHospital->strHospitalNo.GetBuffer(),
		pHospital->strColDate.GetBuffer(),
		pHospital->strColState.GetBuffer(),
		pHospital->strColDetailCode.GetBuffer(),
		pHospital->strColDetailName.GetBuffer(),
		pHospital->strColPhone.GetBuffer(),
		pHospital->nColPost.GetBuffer(),
		pHospital->strColAddr.GetBuffer(),
		pHospital->strColRoadAddr.GetBuffer(),
		pHospital->nColRoadPost.GetBuffer(),
		pHospital->strColName.GetBuffer(),
		pHospital->strColCategory.GetBuffer(),
		pHospital->strColCategoryDetail.GetBuffer(),
		pHospital->nColNumOfPerson.GetBuffer(),
		pHospital->nColNumOfRoom.GetBuffer(),
		pHospital->nColNumOfBed.GetBuffer());

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}
	return TRUE;
}

vector<CHospitalPtr> CHospitalDAO::GetListHospitalFind(CString strHospitalName, CString strHospitalPhone)
{
	vector<CHospitalPtr> resultList;

	//�˻� SQL ���� ����
	CString strSQL;

	strSQL.Format(_T("select\
		a.��ȣ, ���㰡����, b.�������¸�, �󼼿��������ڵ�, �󼼿������¸�, ��������ȭ,\
		�����������ȣ, ��������ü�ּ�, ���θ���ü�ּ�, ���θ�����ȣ, ������, ���±��и�,\
		�Ƿ���������, �Ƿ��μ�, �Կ��Ǽ�, �����, c.��������ڵ�\
		from ���� a, ������������ b,\
		(select e.��ȣ, LISTAGG(g.��������ڵ�, ',') ��������ڵ�\
		from ���� e, ������������ f, ������������� g\
		where e.�������¸� = f.�������°�\
		and g.��ȣ = e.��ȣ\
		group by e.��ȣ) c\
		where a.�������¸� = b.�������°�\
		and c.��ȣ = a.��ȣ\
		and a.������ like '%s%%'                    \
		and a.��������ȭ like '%s%%' \
		"), strHospitalName.GetBuffer(), strHospitalPhone.GetBuffer());

	CRecordset rs(&m_db);

	rs.Open(CRecordset::forwardOnly, strSQL.GetBuffer());

	//SQL ���� ���� ��� ��� 
	while (!rs.IsEOF()) {
		//����Ʈ �����͸� �̿��Ͽ� ��ü������
		CHospitalPtr pHospital = make_shared<CHospital>();
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		rs.GetFieldValue((short)0, pHospital->strHospitalNo);
		rs.GetFieldValue((short)1, pHospital->strColDate);
		rs.GetFieldValue((short)2, pHospital->strColState);
		rs.GetFieldValue((short)3, pHospital->strColDetailCode);
		rs.GetFieldValue((short)4, pHospital->strColDetailName);
		rs.GetFieldValue((short)5, pHospital->strColPhone);
		rs.GetFieldValue((short)6, pHospital->nColPost);
		rs.GetFieldValue((short)7, pHospital->strColAddr);
		rs.GetFieldValue((short)8, pHospital->strColRoadAddr);
		rs.GetFieldValue((short)9, pHospital->nColRoadPost);
		rs.GetFieldValue((short)10, pHospital->strColName);
		rs.GetFieldValue((short)11, pHospital->strColCategory);
		rs.GetFieldValue((short)12, pHospital->strColCategoryDetail);
		rs.GetFieldValue((short)13, pHospital->nColNumOfPerson);
		rs.GetFieldValue((short)14, pHospital->nColNumOfRoom);
		rs.GetFieldValue((short)15, pHospital->nColNumOfBed);
		rs.GetFieldValue((short)16, pHospital->strColTreatSubName);

		rs.MoveNext();

		//�迭�� ����Ʈ ������ ��ü�� �߰��Ѵ� 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

vector<CHospitalSubjectPtr> CHospitalDAO::GetListHospitalSubject()
{
	vector<CHospitalSubjectPtr> resultList;

	//2. SQL ���� ���� 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select * from �����������"));

	//3. SQL ���� ���� ��� ��� 
	while (!rs.IsEOF()) {
		//����Ʈ �����͸� �̿��Ͽ� ��ü������
		CHospitalSubjectPtr pHospitalSubject = make_shared<CHospitalSubject>();
		if (pHospitalSubject == nullptr) return vector<CHospitalSubjectPtr>();

		rs.GetFieldValue((short)0, pHospitalSubject->strSubjectCode);
		rs.GetFieldValue((short)1, pHospitalSubject->strSubjectName);

		rs.MoveNext();

		//�迭�� ����Ʈ ������ ��ü�� �߰��Ѵ� 
		resultList.push_back(pHospitalSubject);
	}
	rs.Close();

	return resultList;
}

BOOL CHospitalDAO::InsertTreatList(CString strHospitalNo, CString pstrState)
{
	//����� SQL ���� �����
	CString strSQL;
	strSQL.Format(_T("insert into ������������� (\
		��ȣ, \
		��������ڵ� \
		) values ( \
		'%s', %s)"), strHospitalNo, pstrState);

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}


BOOL CHospitalDAO::DeleteTreatList(CString strHospitalNo, CString pstrState)
{
	//������ SQL ���� �����
	CString strSQL;
	strSQL.Format(_T("delete from ������������� \
		where ��ȣ = '%s' \
		and ��������ڵ� = '%s'"),strHospitalNo, pstrState);

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}

BOOL CHospitalDAO::DeleteAllTreatList(CString strHospitalNo)
{
	//������ SQL ���� �����
	CString strSQL;
	strSQL.Format(_T("delete from ������������� \
		where ��ȣ = '%s'"), strHospitalNo);

	try {
		m_db.BeginTrans();
		m_db.ExecuteSQL(strSQL.GetBuffer());
		m_db.CommitTrans();
	}
	catch (const CException* pEx) {
		m_db.Rollback();
		TCHAR szErr[100];
		pEx->GetErrorMessage(szErr, sizeof(szErr));
		AfxMessageBox(szErr);
		return FALSE;
	}

	return TRUE;
}