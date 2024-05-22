#pragma once
#include <stdlib.h>
#include <string.h>
typedef struct Stage {
	int height, weight, playerCoordX, playerCoordY, isPlayable;
	char** map;
} Stage;

Stage* NewStage(int, int );
