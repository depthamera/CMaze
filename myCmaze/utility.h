#pragma once
#include <Windows.h>
#include "input.h"
#include <stdio.h>

#define CONSOLE_COLS 120
#define CONSOLE_LINES 50

void InitConsole();
void VisibleCursor(int);
void GotoXY(int, int);
void ShowMessage(char*);

