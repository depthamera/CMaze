#include "upload.h"

static char data[UPLOAD_SIZE_MAX];
static char chunk[UPLOAD_SIZE_MAX * 2 + 1];
static char query[UPLOAD_SIZE_MAX * 5];

void UploadFile(char* name) {
	MYSQL* connection = NULL, con = { 0 };

	mysql_init(&con);
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0);

	if (!connection) {
		ShowMessage("연결에 실패했습니다.");
		return;
	}

	FILE* fp = NULL;

	char fileDir[100] = "./stage/";
	strcat(fileDir, name);
	
	int len, size;

	fp = fopen(fileDir, "rb");
	size = fread(data, 1, UPLOAD_SIZE_MAX, fp);

	mysql_real_escape_string(connection, chunk, data, size);

	char *stat = "insert into stages(stage_name, stage_file) values('%s', '%s')";
	len = snprintf(query, sizeof(stat) + sizeof(chunk), stat, name, chunk);

	mysql_real_query(connection, query, len);
	
	if (mysql_errno(connection)) {
		ShowMessage("업로드 실패");
	}
	else {
		ShowMessage("업로드 성공");
	}

	fclose(fp);
	mysql_close(connection);
}