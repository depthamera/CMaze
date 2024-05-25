#include "download.h"

static int selectedFile, fileCount, isActive, * stageIds;
static char* fileNames[100];


static void Init() {
	selectedFile = fileCount = 0;

	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;

	conn = mysql_init(NULL);
	mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);
	

	mysql_query(conn, "SELECT stage_id, stage_name FROM stages");
	result = mysql_store_result(conn);
	fileCount = mysql_num_rows(result);

	stageIds = (int*)malloc(sizeof(int) * fileCount);
	for (int i = 0; row = mysql_fetch_row(result); i++) {
		stageIds[i] = atoi(row[0]);
		fileNames[i] = (char*)malloc(strlen(row[1]) + 1);
		strcpy(fileNames[i], row[1]);
	}

	mysql_free_result(result);
	mysql_close(conn);
}

static void DownloadFile() {
	MYSQL* conn;
	MYSQL_RES* result;
	MYSQL_ROW row;

	unsigned int* lengths;
	FILE* fp;

	conn = mysql_init(NULL);
	mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);

	if (!conn) {
		ShowMessage("연결에 실패했습니다.");
		return;
	}

	char sql[100] = { 0, };
	char directory[100] = { 0, };

	sprintf(sql, "SELECT stage_file FROM stages WHERE stage_id = '%d'", stageIds[selectedFile]);
	mysql_query(conn, sql);
	result = mysql_store_result(conn);

	row = mysql_fetch_row(result);
	lengths = mysql_fetch_lengths(result);

	sprintf(directory, "./stage/%d_%s", stageIds[selectedFile], fileNames[selectedFile]);
	fp = fopen(directory, "wb");
	
	fwrite(row[0], lengths[0], 1, fp);
	mysql_free_result(result);

	fclose(fp);
	mysql_close(conn);

	ShowMessage("파일을 다운로드했습니다.");
}

static void Quit() {
	isActive = 0;
	for (int i = 0; i < fileCount; i++) {
		free(fileNames[i]);
	}
	free(stageIds);
}

static void Input() {
	switch (GetInput()) {
	case KEY_UP:
		if (--selectedFile == -1) selectedFile = fileCount - 1;
		break;
	case KEY_DOWN:
		if (++selectedFile == fileCount) selectedFile = 0;
		break;
	case KEY_ENTER:
		if (fileCount) DownloadFile();
		break;
	case KEY_Q:
		Quit();
		break;
	}
}

static void Draw() {
	if (fileCount) {
		GotoXY(CONSOLE_COLS / 2 + 25, DOWNLAOD_COORD_Y - 2);
		printf("%d / %d", selectedFile + 1, fileCount);
	}
	GotoXY(CONSOLE_COLS / 2 - 30, DOWNLAOD_COORD_Y - 1);
	printf("┌───────────────────────────────────────────────────────────┐");
	GotoXY(CONSOLE_COLS / 2 - 30, DOWNLAOD_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 + 30, DOWNLAOD_COORD_Y);
	printf("│");
	GotoXY(CONSOLE_COLS / 2 - 30, DOWNLAOD_COORD_Y + 1);
	printf("└───────────────────────────────────────────────────────────┘");
	GotoXY(CONSOLE_COLS / 2 - 16, DOWNLAOD_COORD_Y + 2);
	printf("│ Enter: 다운로드 | Q: 돌아가기 |");

	if (!fileCount) {
		GotoXY(CONSOLE_COLS / 2 - 10, DOWNLAOD_COORD_Y);
		printf("불러올 파일이 없습니다");
	}
	else {
		int len = (int)strlen(fileNames[selectedFile]);
		GotoXY((CONSOLE_COLS - len) / 2 + 1, DOWNLAOD_COORD_Y);
		printf("%s", fileNames[selectedFile]);
	}
}
static void Loop() {
	while (isActive) {
		Draw();
		Input();
		system("cls");
	}
}
void StartDownload() {
	system("cls");
	Init();
	isActive = 1;
	Loop();
}
