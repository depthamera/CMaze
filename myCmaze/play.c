#include "play.h"

static int isActive, playerX, playerY, pivotX, pivotY;
static Stage* stage;

static int CheckValidity() {
	return (stage && stage->startX != -1 && stage->endX != -1);
}

static void LoadStage(char* name) {
	char directory[100];
	stage = (Stage*)malloc(sizeof(Stage));
	sprintf(directory, "./stage/%s", name);

	FILE* fp = fopen(directory, "rb");
	fread((void*)stage, sizeof(Stage), 1, fp);
	fclose(fp);

	playerX = stage->startX;
	playerY = stage->startY;
	pivotX = (CONSOLE_COLS - stage->weight) / 2;
	pivotY = (CONSOLE_LINES - stage->height) / 2;
}

static void DrawMap() {
	GotoXY(pivotX - 1, pivotY - 1);
	for (int i = 0; i < stage->weight + 2; i++) {
		printf("#");
	}
	for (int i = 0; i < stage->height; i++) {
		GotoXY(pivotX - 1, pivotY + i);
		printf("#");
		for (int j = 0; j < stage->weight; j++) {
			printf("%c", stage->map[i][j]);
			if (!stage->map[i][j]) printf("?");
		}
		printf("#");
	}

	GotoXY(pivotX - 1, pivotY + stage->height);
	for (int i = 0; i < stage->weight + 2; i++) {
		printf("#");
	}
}

static void DrawGuide() {
	GotoXY(95, 10);
	printf("방향키: 캐릭터 이동");
	GotoXY(95, 11);
	printf("Q: 나가기");

	GotoXY(92, 15);
	printf("당신의 캐릭터(@)를 이동하여");
	GotoXY(92, 16);
	printf("탈출구($)에 도착하세요!");
}

static void Quit() {
	free(stage);
	isActive = 0;
}

static void TryMove(int dx, int dy) {
	int target_x = playerX + dx;
	int target_y = playerY + dy;

	if (target_x < 0 || target_y < 0 || target_x == stage->weight || target_y == stage->height) return;
	if (stage->map[target_y][target_x] == '#') return;

	GotoXY(pivotX + playerX, pivotY + playerY);
	printf(" ");

	playerX = target_x;
	playerY = target_y;
	GotoXY(pivotX + playerX, pivotY + playerY);
	printf("@");

}

static void Input() {
	switch (GetInput()) {
	case KEY_UP:
		TryMove(0, -1);
		break;
	case KEY_DOWN:
		TryMove(0, 1);
		break;
	case KEY_LEFT:
		TryMove(-1, 0);
		break;
	case KEY_RIGHT:
		TryMove(1, 0);
		break;
	case KEY_Q:
		Quit();
		break;
	}
}

static void CheckClear() {
	if (playerX == stage->endX && playerY == stage->endY) {
		isActive = 0;
		ShowMessage("스테이지 클리어!");
	}
}

static void Loop() {
	while (isActive) {
		Input();
		CheckClear();
	}
}

void PlayStage(char* name) {
	system("cls");
	isActive = 1;
	LoadStage(name);

	if (!CheckValidity()) {
		ShowMessage("플레이할 수 없는 스테이지입니다.");
		isActive = 0;
		return;
	}
	DrawMap();
	DrawGuide();
	Loop();
}