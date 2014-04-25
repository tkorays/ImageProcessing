#pragma once
#include "inc.h"

void copy_and_swap_rb(char *s, char *d, int size);
void wx2cv(wxImage &wx, IplImage *ipl);
void cv2wx(IplImage *ipl, wxImage &wx);
IplImage *cv_from_wx(wxImage &wx);
wxImage wx_from_cv(IplImage *cx);


int get_people_call_back(void *data, int n_columns, char **col_values, char **col_names);