#include "create.h"

int fileCount, selectedFile, isActive;
char* fileNames[100] = { NULL, };

static void Init() {
	system("cls");

	fileCount = 0;
	selectedFile = 0;

	WIN32_FIND_DATA fd;
	char dir[] = "stage/*.stage";
	HANDLE findHandle = FindFirstFile(dir, &fd);

	if (findHandle != INVALID_HANDLE_VALUE) {
		do {
			fileNames[fileCount] = (char*)malloc(strlen(fd.cFileName) + 1);
			strcpy(fileNames[fileCount], fd.cFileName);
			fileCount++;
		} while (FindNextFile(findHandle, &fd));
	}

	for (int i = 0; i < fileCount; i++) {
		printf("%s\n", fileNames[i]);
	}
}

static void Draw() {
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y - 1);
	printf("┌───────────────────────────────────────────────────────────┐");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 + 30, CREATE_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y + 1);
	printf("└───────────────────────────────────────────────────────────┘");
	GotoXY(CONSOLE_COLS / 2 - 35, CREATE_COORD_Y + 2);
	printf("│ E: 스테이지 수정 | C: 스테이지 생성 | D: 스테이지 삭제 | Q: 돌아가기│");

	if (!fileCount) {
		GotoXY(CONSOLE_COLS / 2 - 10, CREATE_COORD_Y);
		printf("불러올 파일이 없습니다");
	}
	else {
		int len = (int)strlen(fileNames[selectedFile]);
		GotoXY((CONSOLE_COLS - len) / 2 + 1, CREATE_COORD_Y);
		printf("%s", fileNames[selectedFile]);
	}
}

static void RemoveFile() {
	char fileName[100] = "./stage/";
	strcat(fileName, fileNames[selectedFile]);
	remove(fileName);
	Init();
}
static void Input() {
	switch (GetInput()) {
	case KEY_UP:
		if (--selectedFile == -1) selectedFile = fileCount - 1;
		break;
	case KEY_DOWN:
		if (++selectedFile == fileCount) selectedFile = 0;
		break;
	case KEY_C:
		StartEdit(NULL);
		break;
	case KEY_D:
		RemoveFile();
		break;
	case KEY_E:
		if (fileCount) StartEdit(fileNames[selectedFile]);
		break;
	case KEY_Q:
		isActive = 0;
		break;
	}
}

static void Loop() {
	while (isActive) {
		Draw();
		Input();
		system("cls");
	}
}

void StartCreate() {
	isActive = 1;
	Init();
	Loop();
}