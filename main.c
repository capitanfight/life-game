#include <SDL.h>
#include "src/globals.h"
#include "src/render.h"
#include "src/game.h"

int main(int argc, char* args []) {
    if (init("Life game", windDim.width, windDim.height)) {
        closeGame();
        return 1;
    }

    int quit = 0;
    while (SDL_WaitEvent(&event) && !quit) {
        if (event.type == SDL_QUIT) {
            quit = 1;
            break;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            drawBackground();

            if (gameState == SETTING) {
                // set the entity position
                addEntity(event);
            } else if (gameState == RUNNING) {
                // next animation frame
                calcNextGen();
            }

            drawEntities();
            drawGrid();

            SDL_RenderPresent(renderer);
        } else if (event.key.state == SDL_PRESSED) {
            if (event.key.keysym.sym == SDLK_SPACE && gameState == SETTING) {
                gameState = RUNNING;

                // change the color of the entities
                drawEntities();
                drawGrid();
                SDL_RenderPresent(renderer);
            } else if (event.key.keysym.sym == SDLK_r) {
                gameState = SETTING;

                clearEntities();

                drawBackground();
                drawGrid();
                SDL_RenderPresent(renderer);
            }
        }
    }

    closeGame();
    return 0;
}