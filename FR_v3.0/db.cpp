#include "db.h"


// exec search
vector<kvpair<int, wxString>> get_people_list() {
	vector<kvpair<int, wxString>> people_list;
	sqlite3* conn = NULL;
	char* errMsg = NULL;
	char sql[256];
	// �����ݿ�
	if (SQLITE_OK != sqlite3_open(DB_FILE_NAME, &conn)) {
		wxMessageBox(wxString(errMsg), _T("���ݿ��ȡ����"));
	}
	sprintf(sql, "select * from people"); // sql���
	sqlite3_exec(conn, sql, &get_people_list_callback, (void*)&people_list, &errMsg);
	sqlite3_close(conn);
	return people_list;
}
// fill data to the var
int get_people_list_callback(void *data, int n_columns, char **col_values, char **col_names) {
	vector<kvpair<int, wxString>>* plist = (vector<kvpair<int, wxString>>*)data;
	int key = atoi(col_values[0]);
	wxString value = wxString(col_values[1]);
	plist->push_back(kvpair<int,wxString>(key,value));
	return 0;
}