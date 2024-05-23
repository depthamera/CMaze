#include "edit.h"

int isActive, cursorX, cursorY, pivotX, pivotY;
char fileDir[100];
Stage *openedStage;

static void GenerateEmptyStage() {
	char str[100] = { 0, };

	openedStage = (Stage*)malloc(sizeof(Stage));
	openedStage->startX = openedStage->startY = openedStage->endX = openedStage->endY = -1;
	for (int i = 0; i < STAGE_HEIGHT_MAX; i++) {
		for (int j = 0; j < STAGE_WEIGHT_MAX; j++) {
			openedStage->map[i][j] = ' ';
		}
	}


	GotoXY(45, 20);
	printf("생성할 스테이지의 높이 (최대 %d): ", STAGE_HEIGHT_MAX);
	scanf("%d", &openedStage->height);
	GotoXY(45, 22);
	printf("생성할 스테이지의 넓이 (최대 %d): ", STAGE_WEIGHT_MAX);
	scanf("%d", &openedStage->weight);

	GotoXY(45, 24);
	printf("생성할 파일의 이름: ");
	scanf("%s", str);
	
	strcpy(fileDir, "./stage/");
	strcat(fileDir, str);
	strcat(fileDir, ".stage");
	
	FILE* fp = fopen(fileDir, "wb");
	fwrite((void*)openedStage, sizeof(Stage), 1, fp);
	fclose(fp);

	pivotX = (CONSOLE_COLS - openedStage->weight) / 2;
	pivotY = (CONSOLE_LINES - openedStage->height) / 2;
}

static void OpenStage(char * name) {
	openedStage = (Stage*)malloc(sizeof(Stage));
	strcpy(fileDir, "./stage/");
	strcat(fileDir, name);

	FILE* fp = fopen(fileDir, "rb");
	fread((void*)openedStage, sizeof(Stage), 1, fp);
	fclose(fp);

	cursorX = cursorY = 0;
	pivotX = (CONSOLE_COLS - openedStage->weight) / 2;
	pivotY = (CONSOLE_LINES - openedStage->height) / 2;
}

static void DrawCursor() {
	int x = pivotX + cursorX;
	int y = pivotY + cursorY;

	GotoXY(x, y);
}

static void DrawMap() {
	GotoXY(pivotX - 1, pivotY - 1);
	for (int i = 0; i < openedStage->weight + 2; i++) {
		printf("#");
	}
	for (int i = 0; i < openedStage->height; i++) {
		GotoXY(pivotX - 1, pivotY + i);
		printf("#");
		for (int j = 0; j < openedStage->weight; j++) {
			printf("%c", openedStage->map[i][j]);
			if (!openedStage->map[i][j]) printf("?");
		}
		printf("#");
	}

	GotoXY(pivotX - 1, pivotY + openedStage->height);
	for (int i = 0; i < openedStage->weight + 2; i++) {
		printf("#");
	}
}

static void DrawGuide() {
	GotoXY(95, 10);
	printf("방향키: 커서 이동");
	GotoXY(95, 11);
	printf("Q: 시작지점");
	GotoXY(95, 12);
	printf("W: 벽");
	GotoXY(95, 13);
	printf("E: 종료지점");

	GotoXY(95, 15);
	printf("S: 저장 후 돌아가기");
}

static void Draw() {
	
	DrawCursor();
}

static void SaveFile() {
	FILE* fp = fopen(fileDir, "wb");
	fwrite((void*)openedStage, sizeof(Stage), 1, fp);
	free(openedStage);
	fclose(fp);
}

static void PutBlock(char b) {
	switch (b) {
	case STAGE_BLOCK_START: {
		if (openedStage->startX != -1) {
			openedStage->map[openedStage->startY][openedStage->startX] = ' ';
			GotoXY(pivotX + openedStage->startX, pivotY + openedStage->startY);
			printf(" ");
		}
		openedStage->startX = cursorX;
		openedStage->startY = cursorY;
		GotoXY(pivotX + openedStage->startX, pivotY + openedStage->startY);
		printf("@");
		break;
		}
	case STAGE_BLOCK_WALL: {
		if (openedStage->startX == cursorX && openedStage->startY == cursorY) {
			openedStage->startX = openedStage->startY = -1;
		}
		GotoXY(pivotX + cursorX, pivotY + cursorY);
		printf("#");
		break;
	}
	}
	openedStage->map[cursorY][cursorX] = b;
}
static void Input() {
	switch (GetInput()) {
	case KEY_UP:
		if (--cursorY == -1) cursorY = openedStage->height - 1;
		break;
	case KEY_DOWN:
		if (++cursorY == openedStage->height) cursorY = 0;
		break;
	case KEY_LEFT:
		if (--cursorX == -1) cursorX = openedStage->weight - 1;
		break;
	case KEY_RIGHT:
		if (++cursorX == openedStage->weight) cursorX = 0;
		break;
	case KEY_Q:
		PutBlock(STAGE_BLOCK_START);
		break;
	case KEY_W:
		PutBlock(STAGE_BLOCK_WALL);
		break;
	case KEY_S:
		SaveFile();
		isActive = 0;
		VisibleCursor(0);
		break;
	}
	
	

}
static void Loop() {
	while (isActive) {
		Draw();
		Input();
	}
}

void StartEdit(char* name) {
	system("cls");
	isActive = 1;
	if (!name) {
		GenerateEmptyStage();
	}
	else {
		OpenStage(name);
	}
	system("cls");

	VisibleCursor(1);
	DrawMap();
	DrawGuide();
	Loop();
}