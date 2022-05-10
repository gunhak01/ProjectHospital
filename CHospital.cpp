#include "pch.h"
#include "CHospital.h"

vector<CHospitalPtr> CHospitalDAO::GetListHospital()
{
	vector<CHospitalPtr> resultList;

	//SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select\
		a.번호, a.인허가일자, d.영업상태명, a.상세영업상태코드, a.상세영업상태명, a.소재지전화,\
		a.소재지우편번호, a.소재지전체주소, a.도로명전체주소, a.도로명우편번호, a.사업장명, a.업태구분명,\
		a.의료기관종별명, a.의료인수, a.입원실수, a.병상수\
		,listagg(c.진료과목명, ',')\
		,listagg(b.진료과목코드, ',')\
		from 병원 a, 병원진료과목목록 b, 병원진료과목 c, 병원영업상태 d\
		where  a.번호 = b.번호\
		and a.영업상태명 = d.영업상태값\
		and c.진료과목코드 = b.진료과목코드\
		group by a.번호, a.인허가일자, d.영업상태명, a.상세영업상태코드, a.상세영업상태명, a.소재지전화,\
		a.소재지우편번호, a.소재지전체주소, a.도로명전체주소, a.도로명우편번호, a.사업장명, a.업태구분명,\
		a.의료기관종별명, a.의료인수, a.입원실수, a.병상수;"));

	//SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체 생성함
		CHospitalPtr pHospital = make_shared<CHospital>(); //new CHospital;
		if (pHospital == nullptr) return vector<CHospitalPtr>();

		//DB에서 조회된 Hospital 1건을 pHospital 객체로 설정하는 부분  
		rs.GetFieldValue(_T("번호"), pHospital->strHospitalNo);
		rs.GetFieldValue(_T("인허가일자"), pHospital->strColDate);
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

		//배열에 스마트 포인터 객체(pHospital)를 추가한다 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

CHospitalPtr CHospitalDAO::GetHospital(CString strHospitalNo)
{
	//스마트 포인터를 이용하여 객체생성함
	CHospitalPtr pHospital = make_shared<CHospital>();

	//SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select\
		a.번호, 인허가일자, b.영업상태명, 상세영업상태코드, 상세영업상태명, 소재지전화,\
		소재지우편번호, 소재지전체주소, 도로명전체주소, 도로명우편번호, 사업장명, 업태구분명,\
		의료기관종별명, 의료인수, 입원실수, 병상수, c.진료과목코드\
		from 병원 a, 병원영업상태 b,\
		(select e.번호, LISTAGG(g.진료과목코드, ',') 진료과목코드\
		from 병원 e, 병원영업상태 f, 병원진료과목목록 g\
		where e.영업상태명 = f.영업상태값\
		and g.번호 = e.번호\
		group by e.번호) c\
		where a.영업상태명 = b.영업상태값\
		and c.번호 = a.번호\
		and a.번호 = ") + strHospitalNo);

	//SQL 구문 실행 결과 얻기 
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
	//수정할 SQL 구문 생성
	CString strSQL;
	
	strSQL.Format(_T("update 병원 set \
		인허가일자='%s', 영업상태명='%s', 상세영업상태코드='%s', 상세영업상태명 ='%s', 소재지전화='%s', \
		소재지우편번호='%s', 소재지전체주소='%s', 도로명전체주소='%s', 도로명우편번호='%s', 사업장명='%s', \
		업태구분명='%s', 의료기관종별명='%s', 의료인수='%s', 입원실수='%s', 병상수='%s' \
		where 번호='%s'"),
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
	//등록할 SQL 구문 생성
	CString strSQL;
	strSQL.Format(_T("insert into 병원 (\
		번호, 인허가일자, 영업상태명, 상세영업상태코드, 상세영업상태명, 소재지전화, \
		소재지우편번호, 소재지전체주소, 도로명전체주소, 도로명우편번호, 사업장명, 업태구분명, \
		의료기관종별명, 의료인수, 입원실수, \
		병상수) values (\
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

	//검색 SQL 구문 생성
	CString strSQL;

	strSQL.Format(_T("select\
		a.번호, 인허가일자, b.영업상태명, 상세영업상태코드, 상세영업상태명, 소재지전화,\
		소재지우편번호, 소재지전체주소, 도로명전체주소, 도로명우편번호, 사업장명, 업태구분명,\
		의료기관종별명, 의료인수, 입원실수, 병상수, c.진료과목코드\
		from 병원 a, 병원영업상태 b,\
		(select e.번호, LISTAGG(g.진료과목코드, ',') 진료과목코드\
		from 병원 e, 병원영업상태 f, 병원진료과목목록 g\
		where e.영업상태명 = f.영업상태값\
		and g.번호 = e.번호\
		group by e.번호) c\
		where a.영업상태명 = b.영업상태값\
		and c.번호 = a.번호\
		and a.사업장명 like '%s%%'                    \
		and a.소재지전화 like '%s%%' \
		"), strHospitalName.GetBuffer(), strHospitalPhone.GetBuffer());

	CRecordset rs(&m_db);

	rs.Open(CRecordset::forwardOnly, strSQL.GetBuffer());

	//SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체생성함
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

		//배열에 스마트 포인터 객체를 추가한다 
		resultList.push_back(pHospital);
	}
	rs.Close();

	return resultList;
}

vector<CHospitalSubjectPtr> CHospitalDAO::GetListHospitalSubject()
{
	vector<CHospitalSubjectPtr> resultList;

	//2. SQL 구문 실행 
	CRecordset rs(&m_db);
	rs.Open(CRecordset::forwardOnly, _T("select * from 병원진료과목"));

	//3. SQL 구문 실행 결과 얻기 
	while (!rs.IsEOF()) {
		//스마트 포인터를 이용하여 객체생성함
		CHospitalSubjectPtr pHospitalSubject = make_shared<CHospitalSubject>();
		if (pHospitalSubject == nullptr) return vector<CHospitalSubjectPtr>();

		rs.GetFieldValue((short)0, pHospitalSubject->strSubjectCode);
		rs.GetFieldValue((short)1, pHospitalSubject->strSubjectName);

		rs.MoveNext();

		//배열에 스마트 포인터 객체를 추가한다 
		resultList.push_back(pHospitalSubject);
	}
	rs.Close();

	return resultList;
}

BOOL CHospitalDAO::InsertTreatList(CString strHospitalNo, CString pstrState)
{
	//등록할 SQL 구문 만든다
	CString strSQL;
	strSQL.Format(_T("insert into 병원진료과목목록 (\
		번호, \
		진료과목코드 \
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
	//삭제할 SQL 구문 만든다
	CString strSQL;
	strSQL.Format(_T("delete from 병원진료과목목록 \
		where 번호 = '%s' \
		and 진료과목코드 = '%s'"),strHospitalNo, pstrState);

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
	//삭제할 SQL 구문 만든다
	CString strSQL;
	strSQL.Format(_T("delete from 병원진료과목목록 \
		where 번호 = '%s'"), strHospitalNo);

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