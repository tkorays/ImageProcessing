#include "db.h"


// exec search
vector<kvpair<int, wxString>> get_people_list() {
	vector<kvpair<int, wxString>> people_list;
	sqlite3* conn = NULL;
	char* errMsg = NULL;
	char sql[256];
	// 打开数据库
	if (SQLITE_OK != sqlite3_open(DB_FILE_NAME, &conn)) {
		wxMessageBox(wxString(errMsg), _T("数据库读取错误！"));
	}
	sprintf(sql, "select * from people"); // sql语句
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

int get_people_id(wxString n) {
	int index;
	sqlite3* conn = NULL;
	char* errMsg = NULL; char sql[256];
	// 打开数据库
	if (SQLITE_OK != sqlite3_open(DB_FILE_NAME, &conn)) {
		wxMessageBox(wxString(errMsg), _T("数据库读取错误！"));
	}
	sprintf(sql, "select * from people where pname='%s'", n.ToStdString().data()); // sql语句
	sqlite3_exec(conn, sql, &get_people_id_callback, (void*)&index, &errMsg);
	sqlite3_close(conn);
	return index;
}
int get_people_id_callback(void *data, int n_columns, char **col_values, char **col_names) {
	int* index = (int*)data;
	*index = atoi(col_values[0]);
	return 0;
}

vector<wxString> get_pic_list(int userid) {
	vector<wxString> piclist;
	sqlite3* conn = NULL;
	char* errMsg = NULL;char sql[256];
	// 打开数据库
	if (SQLITE_OK != sqlite3_open(DB_FILE_NAME, &conn)) {
		wxMessageBox(wxString(errMsg), _T("数据库读取错误！"));
	}
	sprintf(sql, "select * from pface where pid=%d",userid); // sql语句
	sqlite3_exec(conn, sql, &get_pic_list_callback, (void*)&piclist, &errMsg);
	sqlite3_close(conn);
	return piclist;
}
int get_pic_list_callback(void *data, int n_columns, char **col_values, char **col_names) {
	vector<wxString>* piclist = (vector<wxString>*)data;
	piclist->push_back(wxString(col_values[2]));
	return 0;
}