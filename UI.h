#pragma once
#include <stdbool.h>

extern int cursor_x;
extern int cursor_y;

void goto_xy(int x, int y);
void CursorView(bool show);
void textcolor(int color_num);