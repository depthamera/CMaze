#include "edit.h"

static int isActive, cursorX, cursorY, pivotX, pivotY;
static char fileDir[100];
static Stage *openedStage;

static void GenerateEmptyStage() {
	char str[100] = { 0, };

	openedStage = (Stage*)malloc(sizeof(Stage));
	openedStage->height = openedStage->weight = openedStage->startX = openedStage->startY = openedStage->endX = openedStage->endY = -1;
	for (int i = 0; i < STAGE_HEIGHT_MAX; i++) {
		for (int j = 0; j < STAGE_WEIGHT_MAX; j++) {
			openedStage->map[i][j] = ' ';
		}
	}


	while (openedStage->height == -1 || openedStage->height < 1 || openedStage->height > STAGE_HEIGHT_MAX) {
		system("cls");
		GotoXY(45, 20);
		printf("생성할 스테이지의 높이 (최대 %d): ", STAGE_HEIGHT_MAX);
		scanf("%d", &openedStage->height);
	}
	
	
	while (openedStage->weight == -1 || openedStage->weight < 1 || openedStage->weight > STAGE_WEIGHT_MAX) {
		system("cls");
		GotoXY(45, 20);
		printf("생성할 스테이지의 넓이 (최대 %d): ", STAGE_WEIGHT_MAX);
		scanf("%d", &openedStage->weight);
	}

	system("cls");
	GotoXY(45, 20);
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
	GotoXY(95, 14);
	printf("R: 지우기");
	GotoXY(95, 16);
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
	if (openedStage->startX == cursorX && openedStage->startY == cursorY) {
		openedStage->startX = openedStage->startY = -1;
	}
	if (openedStage->endX == cursorX && openedStage->endY == cursorY) {
		openedStage->endX = openedStage->endY = -1;
	}

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
	case STAGE_BLOCK_END: {
		if (openedStage->endX != -1) {
			openedStage->map[openedStage->endY][openedStage->endX] = ' ';
			GotoXY(pivotX + openedStage->endX, pivotY + openedStage->endY);
			printf(" ");
		}
		openedStage->endX = cursorX;
		openedStage->endY = cursorY;
		GotoXY(pivotX + openedStage->endX, pivotY + openedStage->endY);
		printf("$");
		break;
	}
	case STAGE_BLOCK_WALL: {
		GotoXY(pivotX + cursorX, pivotY + cursorY);
		printf("#");
		break;
	default:
		b = ' ';
		GotoXY(pivotX + cursorX, pivotY + cursorY);
		printf(" ");
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
	case KEY_E:
		PutBlock(STAGE_BLOCK_END);
		break;
	case KEY_S:
		SaveFile();
		isActive = 0;
		VisibleCursor(0);
		break;
	case KEY_R:
		PutBlock(-1);
		break;
	}
}

static void Loop() {
	while (isActive) {
		Draw();
		Input();
	}
}

static void Init(char * name) {
	system("cls");
	isActive = 1;
	cursorX = cursorY = 0;
	if (!name) {
		GenerateEmptyStage();
		system("cls");
	}
	else {
		OpenStage(name);
	}
	VisibleCursor(1);
	DrawMap();
	DrawGuide();
}
void StartEdit(char* name) {
	Init(name);
	Loop();
}