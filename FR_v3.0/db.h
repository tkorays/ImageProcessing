#pragma once
#include "inc.h"
#include "conf.h"
#include "sqlite3.h"
#include "kvpair.h"
using namespace tk;


/*
	���ݿ��д���Լ�����
	����һ���԰�����ȫ�������ڴ棿���ǲ�Ҫ�˰�
*/

// ��ȡpeople�����ص�����
vector<kvpair<int, wxString>> get_people_list();
int get_people_list_callback(void *data, int n_columns, char **col_values, char **col_names);