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
	case 101:
		return KEY_E;
	case 113:
		return KEY_Q;
	case 115:
		return KEY_S;
	case 117:
		return KEY_U;
	case 119:
		return KEY_W;
	default:
		return key;
	}
	
}