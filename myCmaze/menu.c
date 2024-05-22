#include "menu.h"

int selectedMenu = 0;
char* menu[MENU_MAX] = { {"플 레 이"}, {"제    작"}, {"다운로드"}, {"종    료"} };
void (*action[MENU_MAX])();

static void Exit() { exit(0); }

static void Draw() {
	for(int i = 0; i < MENU_MAX; i++) {
		GotoXY(MENU_COORD_X, MENU_COORD_Y + MENU_COORD_DISTANCE_Y * i);
		printf("% s", menu[i]);
	}
	GotoXY(MENU_COORD_X - 1, MENU_COORD_Y + MENU_COORD_DISTANCE_Y * selectedMenu);
	printf(">");
}

static void Input() {
	switch (GetInput()) {
	case KEY_ENTER:
		GotoXY(0, 0);
		if (action[selectedMenu]) action[selectedMenu]();
		break;
	case KEY_UP:
		if (--selectedMenu == -1) selectedMenu = MENU_MAX - 1;
		break;
	case KEY_DOWN:
		if (++selectedMenu == MENU_MAX) selectedMenu = 0;
		break;
	}
}

static void Loop() {
	while (1) {
		Draw();
		Input();
		system("cls");
	}
}

void MenuStart() {
	action[1] = StartCreate;
	action[3] = Exit;
	Loop();
}