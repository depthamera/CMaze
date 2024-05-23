#include "utility.h"

HANDLE consoleHandle = NULL;
CONSOLE_CURSOR_INFO cursorInfo = { 0 };

void InitConsole() {
	// �ܼ�â�� ũ�⸦ ����
	char option[100] = { 0, };
	sprintf(option, "mode con:cols=%d lines=%d", CONSOLE_COLS, CONSOLE_LINES);
	system(option);

	// Ŀ���� ǥ�� ���ο� ũ�⸦ ����
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
} 

void VisibleCursor(int b) {
	cursorInfo.bVisible = b;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Ŀ���� �Է¹��� ��ġ�� �̵�
void GotoXY(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(consoleHandle, pos);
}