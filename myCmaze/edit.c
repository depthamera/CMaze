#include "edit.h"

int isActive;
static void GenerateEmptyStage() {
	int h, w;
	char str[100] = { 0, }, fileName[100] = "./stage/";

	GotoXY(45, 20);
	printf("생성할 스테이지의 높이: ");
	scanf("%d", &h);
	GotoXY(45, 22);
	printf("생성할 스테이지의 넓이: ");
	scanf("%d", &w);

	GotoXY(45, 24);
	printf("생성할 파일의 이름: ");
	scanf("%s", str);
	strcat(fileName, str);
	strcat(fileName, ".stage");
	Stage* stage = NewStage(h, w);
	FILE* fp = fopen(fileName, "wb");
	fwrite((void*)stage, sizeof(Stage*), 1, fp);
}

static void Draw() {
	
}
static void Input() {

}
static void Loop() {
	while (isActive) {
		Draw();
		Input();
		system("cls");
	}
}

void StartEdit(char* name) {
	system("cls");
	isActive = 1;
	if (!name) {
		GenerateEmptyStage();
	}
	Loop();
}