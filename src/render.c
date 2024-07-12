#include "render.h"
#include "globals.h"
#include "game.h"
#include <stdlib.h>
#include <SDL.h>


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

int init(const char* title, int w, int h) {
    SDL_Init(SDL_INIT_VIDEO);

    if (CreateWindowAndRenderer(title, w, h)) return 1;

    gameGrid = calloc(gridRows * gridColumns, sizeof(int));
    if (gameGrid == NULL) {
        SDL_Log("cannot create the pointer to game grid");
        return 1;
    }

    drawBackground();
    drawGrid();
    SDL_RenderPresent(renderer);

    return 0;
}

int CreateWindowAndRenderer(const char* title, int w, int h) {

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        closeGame();
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        closeGame();
        return 1;
    }
    return 0;
}

void closeGame() {
    if (gridCache) free(gridCache);
    if (gameGrid) free(gameGrid);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// basic drawing functions
void drawLine(point p1, point p2, color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);

    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

void drawRect(point p, dimensions dim, color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);

    SDL_Rect rect= {p.x, p.y, dim.width, dim.height};

    SDL_RenderFillRect(renderer, &rect);
}

// game drawing
void drawBackground() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    SDL_RenderClear(renderer);
}

void drawGrid() {
    if (gridCache == NULL) {
        gridCache = malloc(sizeof(point) * (gridRows + gridRows - 2) * 2);
        if (gridCache == NULL) {
            SDL_Log("cannot create the pointer to grid cache");
            closeGame();
            return;
        }

        for (int i = 1; i < gridRows*2-1; i+=2) {
            const point p1 = {0, tile.height*(i/2+1)};
            const point p2 = {windDim.width, tile.height*(i/2+1)};

            const int offset = i - 1;

            *(gridCache + offset) = p1;
            *(gridCache + offset + 1) = p2;
        }
        for (int i = 1; i < gridColumns*2-1; i+=2) {
            const point p1 = {tile.width*(i/2+1), 0};
            const point p2 = {tile.width*(i/2+1), windDim.height};

            const int offset = i-1 + (gridRows-1)*2;

            *(gridCache + offset) = p1;
            *(gridCache + offset + 1) = p2;
        }
    }
    for (int i = 0; i < (gridRows + gridRows - 2)*2; i+=2) {
        drawLine(*(gridCache+i), *(gridCache+i+1), lineColor);
    }
}

void drawEntity(point position) {
    if (position.x >= gridColumns || position.y >= gridRows) {
        SDL_Log("enity out of bounds.");
        return;
    }

    point origin = {position.x * tile.width, position.y * tile.height};

    if (gameState == SETTING)
        drawRect(origin, tile, settingEntityColor);
    else if (gameState == RUNNING)
        drawRect(origin, tile, runningEntityColor);
}