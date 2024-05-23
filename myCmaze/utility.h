#pragma once
#include <Windows.h>
#include <stdio.h>
#pragma warning(disable:4996)

#define CONSOLE_COLS 120
#define CONSOLE_LINES 50

void InitConsole();
void VisibleCursor(int);
void GotoXY(int, int);

