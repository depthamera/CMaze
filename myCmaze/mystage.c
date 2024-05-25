#include "mystage.h"

static int fileCount, selectedFile, isActive;
static char* fileNames[100];

static void Init() {
	system("cls");

	fileCount = 0;
	selectedFile = 0;

	WIN32_FIND_DATA fd;
	char dir[] = "stage/*.stage";
	HANDLE findHandle = FindFirstFile(dir, &fd);

	if (findHandle != INVALID_HANDLE_VALUE) {
		do {
			fileNames[fileCount] = (char*)malloc(sizeof(fd.cFileName));
			strcpy(fileNames[fileCount], fd.cFileName);
			fileCount++;
		} while (FindNextFile(findHandle, &fd));
	}

	for (int i = 0; i < fileCount; i++) {
		printf("%s\n", fileNames[i]);
	}
}

static void Draw() {
	if (fileCount) {
		GotoXY(CONSOLE_COLS / 2 + 25, CREATE_COORD_Y - 2);
		printf("%d / %d", selectedFile + 1, fileCount);
	}
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y - 1);
	printf("┌───────────────────────────────────────────────────────────┐");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 + 30, CREATE_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y + 1);
	printf("└───────────────────────────────────────────────────────────┘");
	GotoXY(CONSOLE_COLS / 2 - 10, CREATE_COORD_Y + 2);
	printf("| Enter: 스테이지 플레이 |");
	GotoXY(CONSOLE_COLS / 2 - 28, CREATE_COORD_Y + 3);
	printf("│ E: 스테이지 수정 | C: 스테이지 생성 | D: 스테이지 삭제 |");
	GotoXY(CONSOLE_COLS / 2 - 17, CREATE_COORD_Y + 4);
	printf("| U: 스테이지 업로드 | Q: 돌아가기│");

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

static void Quit() {
	isActive = 0;
	for (int i = 0; i < fileCount; i++) {
		free(fileNames[i]);
	}
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
	case KEY_U:
		if(fileCount) UploadFile(fileNames[selectedFile]);
		break;
	case KEY_Q:
		Quit();
		break;
	case KEY_ENTER:
		if (fileCount) PlayStage(fileNames[selectedFile]);
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