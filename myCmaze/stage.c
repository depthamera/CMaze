#include "stage.h"

Stage* NewStage(int height, int weight) {
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	if (stage) {
		stage->height = height;
		stage->weight = weight;
		stage->playerCoordX = 0;
		stage->playerCoordY = 0;
		stage->isPlayable = 0;
		stage->map = (char**)malloc(sizeof(char*) * height);
		if (stage->map) {
			for (int i = 0; i < height; i++) {
				stage->map[i] = (char*)malloc(sizeof(char) * weight);
				memset(stage->map[i], ' ', sizeof(char) * weight);
			}
		}
	}
	return stage;
}