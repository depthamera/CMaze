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

void ShowMessage(char* msg) {
	int is_active = 1;
	GotoXY(CONSOLE_COLS / 2 - 30, CONSOLE_LINES / 2 - 3);
	printf("��������������������������������������������������������������������������������������������������������������������������");
	GotoXY(CONSOLE_COLS / 2 - 30, CONSOLE_LINES / 2 - 2);
	printf("��");
	GotoXY((CONSOLE_COLS - strlen(msg)) / 2 + 2, CONSOLE_LINES / 2 - 2);
	printf("%s", msg);
	GotoXY(CONSOLE_COLS / 2 + 30, CONSOLE_LINES / 2 - 2);
	printf("��");
	GotoXY(CONSOLE_COLS / 2 - 30, CONSOLE_LINES / 2 - 1);
	printf("��������������������������������������������������������������������������������������������������������������������������");
	GotoXY((CONSOLE_COLS - strlen(msg)) / 2 + 4, CONSOLE_LINES / 2);
	printf("Enter�� ���� ���");

	while (is_active) {
		switch (GetInput()) {
		case KEY_ENTER:
			is_active = 0;
			break;
		}
	}
}