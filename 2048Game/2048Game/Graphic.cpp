#include "Header.h"
#include "Graphic.h"

//using ANSI color table 
//reference: https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences (section: 4-bit Colours)
string GetColor(int a) {
	string s = to_string(a);
	if (a == 2)
		return "\x1B[32m";
	if (a == 4)
		return "\x1B[92m";
	if (a == 8)
		return "\x1B[31m";
	if (a == 16)
		return "\x1B[91m";
	if (a == 32)
		return "\x1B[33m";
	if (a == 64)
		return "\x1B[93m";
	if (a > 64)
		return "\x1B[94m";
	if (a == 0)
		return "\x1B[37m";
}

//reference: https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console (section: Di chuyển con trỏ đến vị trí (x; y))
void GoTo(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = posX;
	Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

//reference: https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console (section: Ẩn/Hiện con trỏ)
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
