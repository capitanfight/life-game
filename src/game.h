#pragma once
#include <SDL.h>

void addEntity(SDL_Event event);
void drawEntities();
void calcNextGen();
void clearEntities();

enum gameStates { SETTING, RUNNING };
extern int gameState;

enum tileState { DEAD = 0, ALIVE };
extern int* gameGrid;