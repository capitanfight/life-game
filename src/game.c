#include "game.h"
#include "globals.h"
#include "render.h"

#include <stdlib.h>
#include <string.h>
#include <SDL.h>

void addEntity(SDL_Event event) {
    point mouseClick = {event.button.x / tile.width, event.button.y / tile.height};
    int offset = (mouseClick.x) + (mouseClick.y*gridColumns);

    *(gameGrid + offset) = ALIVE;
}

void drawEntities() {
    for (int i = 0; i < (gridRows * gridColumns); i++) {
        if (*(gameGrid+i) == ALIVE) {
            point pos =  { i%gridColumns, i/gridRows };
            drawEntity(pos);
        }
    }
}

void calcNextGen() {
    int* newGen = malloc(sizeof(int) * (gridRows * gridColumns));
    if (newGen == NULL) {
        SDL_Log("cannot create the pointer to new gen");
        closeGame();
        return;
    }
    memcpy(newGen, gameGrid, sizeof(int) * (gridRows * gridColumns));

    for (int i = 0; i < (gridRows * gridColumns); i++) {
        int surroundingAliveEntity = 0;
        for (int r = -1; r <= 1; r++) {
            int yPos = i/gridColumns;
            for (int c = -1; c <= 1; c++) {
                int xPos = i%gridColumns;
                int offset = (c+xPos) + ((r+yPos)*gridColumns);

                // out of the bounds of the array
                if (offset < 0 || offset >= gridRows*gridColumns) continue;
                if (offset == i) continue;
                // checking for the end of the grid
                int isOffsetOnBorder = ((offset+1)%gridRows==0 || offset%gridRows==0) ? 1 : 0;
                int isCurrentTileOnBorder = ((i+1)%gridRows==0 || i%gridRows==0) ? 1 : 0;
                if ((isOffsetOnBorder && isCurrentTileOnBorder) && c != 0) continue;

                if (*(gameGrid+offset) == ALIVE) {
                    surroundingAliveEntity++;
                }
            }
        }

        int cellState = *(gameGrid+i);
        if (cellState == ALIVE && (surroundingAliveEntity < 2 || surroundingAliveEntity > 3)) {
            *(newGen+i) = DEAD;
        } else if (cellState == DEAD && surroundingAliveEntity == 3) {
            *(newGen+i) = ALIVE;
        }
    }

    free(gameGrid);
    gameGrid = newGen;
}

void clearEntities() {
    free(gameGrid);
    gameGrid = calloc(gridRows * gridColumns, sizeof(int));
}

int gameState = SETTING;
int* gameGrid = NULL;