#pragma once
#define STAGE_HEIGHT_MAX 30
#define STAGE_WEIGHT_MAX 60
#define STAGE_BLOCK_START '@'
#define STAGE_BLOCK_WALL '#'
#define STAGE_BLOCK_END '$'

typedef struct Stage {
	int height, weight, startX, startY, endX, endY;
	char map[STAGE_HEIGHT_MAX][STAGE_WEIGHT_MAX];
} Stage;
