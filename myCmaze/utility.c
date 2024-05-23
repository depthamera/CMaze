#include "utility.h"

HANDLE consoleHandle = NULL;
CONSOLE_CURSOR_INFO cursorInfo = { 0 };

void InitConsole() {
	// 콘솔창의 크기를 지정
	char option[100] = { 0, };
	sprintf(option, "mode con:cols=%d lines=%d", CONSOLE_COLS, CONSOLE_LINES);
	system(option);

	// 커서의 표시 여부와 크기를 지정
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
} 

void VisibleCursor(int b) {
	cursorInfo.bVisible = b;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// 커서를 입력받은 위치로 이동
void GotoXY(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(consoleHandle, pos);
}