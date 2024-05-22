#include "create.h"

int stageCount, selectedStage;
char* stageNames[100] = { NULL, };

static void Init() {
	system("cls");

	stageCount = 0;
	WIN32_FIND_DATA fd;
	char dir[] = "stage/*.stage";
	HANDLE findHandle = FindFirstFile(dir, &fd);

	if (findHandle != INVALID_HANDLE_VALUE) {
		do {
			stageNames[stageCount] = (char*)malloc(strlen(fd.cFileName) + 1);
			strcpy(stageNames[stageCount], fd.cFileName);
			stageCount++;
		} while (FindNextFile(findHandle, &fd));
	}

	for (int i = 0; i < stageCount; i++) {
		printf("%s\n", stageNames[i]);
	}
}

static void Draw() {
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y - 1);
	printf("��������������������������������������������������������������������������������������������������������������������������");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y);
	printf("��");
	GotoXY(CONSOLE_COLS / 2 + 30, CREATE_COORD_Y);
	printf("��");
	GotoXY(CONSOLE_COLS / 2 - 30, CREATE_COORD_Y + 1);
	printf("��������������������������������������������������������������������������������������������������������������������������");
	GotoXY(CONSOLE_COLS / 2 - 35, CREATE_COORD_Y + 2);
	printf("�� E: �������� ���� | C: �������� ���� | D: �������� ���� | Q: ���ư��⦢");

	if (!stageCount) {
		GotoXY(CONSOLE_COLS / 2 - 10, CREATE_COORD_Y);
		printf("�ҷ��� ������ �����ϴ�");
	}
	else {
		int len = strlen(stageNames[selectedStage]);
		GotoXY((CONSOLE_COLS - len) / 2 + 1, CREATE_COORD_Y);
		printf("%s", stageNames[selectedStage]);
	}
}

static void Input() {
	switch (GetInput()) {
		
	}
}

static void Loop() {
	while (1) {
		Draw();
		Input();
		system("cls");
	}
}

void StartCreate() {
	Init();
	Loop();
}