#pragma once
#include "inc.h"
#include "conf.h"
#include "sqlite3.h"
#include "kvpair.h"
using namespace tk;


/*
	数据库读写类以及函数
	可以一次性把数据全部读到内存？还是不要了吧
*/

// 读取people表和其回调函数
vector<kvpair<int, wxString>> get_people_list();
int get_people_list_callback(void *data, int n_columns, char **col_values, char **col_names);