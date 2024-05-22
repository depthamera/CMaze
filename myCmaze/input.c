#include "input.h"

int GetInput() {
	int key = getch();

	if (key == 224) {
		switch (getch()) {
		case 72:
			return KEY_UP;
		case 75:
			return KEY_LEFT;
		case 77:
			return KEY_RIGHT;
		case 80:
			return KEY_DOWN;
		}
	}

	switch (key) {
	case 13:
		return KEY_ENTER;
	case 99:
		return KEY_C;
	case 100:
		return KEY_D;
	case 113:
		return KEY_Q;
	default:
		return key;
	}
	
}