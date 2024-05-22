#include "main.h"

int main() {
	InitConsole();

	/*WIN32_FIND_DATA fd;
	char dir[] = "stages/*.stage";
	HANDLE handle_find = FindFirstFile(dir, &fd);

	if (handle_find != INVALID_HANDLE_VALUE) {
		do {
			printf("%s\n", (char*)fd.cFileName);
		} while (FindNextFile(handle_find, &fd));
	}*/
	

	MenuStart();
}