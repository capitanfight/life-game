#pragma once
#include <SDL.h>
#include "globals.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;

int init(const char* title, int w, int h);
int CreateWindowAndRenderer(const char* title, int w, int h);
void closeGame();

void drawLine(point p1, point p2, color c);
void drawRect(point p1, dimensions dim, color c);

void drawBackground();
void drawGrid();
void drawEntity();