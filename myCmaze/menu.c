#include "menu.h"

static int selectedMenu = 0;
static char* menu[MENU_MAX] = { {"내 파 일"}, {"다운로드"}, {"종    료"} };
static void (*action[MENU_MAX])();

static void Exit() { exit(0); }


static void Draw() {
	GotoXY(MENU_COORD_X - 19, MENU_COORD_Y - 10);
	printf(" ,-----.,--.   ,--.  ,---.  ,-------. ,------. ");
	GotoXY(MENU_COORD_X - 19, MENU_COORD_Y - 9);
	printf("'  .--./|   `.'   | /        `--.   /|  .---' ");
	GotoXY(MENU_COORD_X - 19, MENU_COORD_Y - 8);
	printf("|  |    |  |'.'|  ||  .-.  |  /   /  |  `--,  ");
	GotoXY(MENU_COORD_X - 19, MENU_COORD_Y - 7);
	printf("'  '--' |  |   |  ||  | |  | /   `--.|  `---. ");
	GotoXY(MENU_COORD_X - 19, MENU_COORD_Y - 6);
	printf(" `-----'`--'   `--'`--' `--'`-------'`------' ");
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
	action[0] = StartCreate;
	action[1] = StartDownload;
	action[2] = Exit;
	Loop();
}