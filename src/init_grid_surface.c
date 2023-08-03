#include <fonctions.h>
#include "display.h"

#include "SDL2/SDL_image.h"

void init_grid_surface(sudoku *sudoku_tab)
{
    sudoku_tab -> gridTexture = SDL_CreateTexture(sudoku_tab -> renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, GRID_SIZE + 1, GRID_SIZE);
    SDL_SetRenderTarget(sudoku_tab -> renderer, sudoku_tab -> gridTexture);
    SDL_SetRenderDrawColor(sudoku_tab->renderer, 156, 86, 232, 255);
    SDL_RenderClear(sudoku_tab->renderer);
    SDL_SetRenderDrawColor(sudoku_tab -> renderer, 100, 100, 100, 255);

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            SDL_Rect rectangle = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderDrawRect(sudoku_tab->renderer, &rectangle);
        }
    }
    SDL_SetRenderDrawColor(sudoku_tab -> renderer, 0, 0, 0, 255);
    for (int x = 0; x <= 3; x++)
    {
        for (int y = 0; y <= 3; y++)
        {
            SDL_Point A = {0, y * CELL_SIZE * 3};
            SDL_Point B = {WINDOW_WIDTH, y * CELL_SIZE * 3};
            SDL_RenderDrawLine(sudoku_tab -> renderer, A.x, A.y, B.x, B.y);

            SDL_Point X = {x * CELL_SIZE * 3, 0};
            SDL_Point Y = {x * CELL_SIZE * 3, WINDOW_HEIGHT};
            SDL_RenderDrawLine(sudoku_tab -> renderer, X.x, X.y, Y.x, Y.y);
        }
    }
    SDL_SetRenderTarget(sudoku_tab -> renderer, NULL);
}

void quitGraphics(sudoku *sudoku_tab)
{
    for (int i = 0; i < 9; i++)
    {
        SDL_DestroyTexture(sudoku_tab -> cellTextures[i]);
        SDL_DestroyTexture(sudoku_tab -> cellTexturesPlayer[i]);
    }
    SDL_DestroyTexture(sudoku_tab -> gridTexture);
    SDL_DestroyTexture(sudoku_tab -> victory);
    SDL_DestroyTexture(sudoku_tab -> loosing);
    SDL_DestroyTexture(sudoku_tab -> button_start);
    SDL_DestroyTexture(sudoku_tab -> button_finished);
    SDL_DestroyTexture(sudoku_tab -> almost_validated);
    SDL_DestroyTexture(sudoku_tab -> almost_continued);
    SDL_DestroyRenderer(sudoku_tab -> renderer);
    SDL_DestroyRenderer(sudoku_tab -> new_game);
    SDL_DestroyRenderer(sudoku_tab -> try_again);
    SDL_DestroyRenderer(sudoku_tab -> level_one);
    SDL_DestroyRenderer(sudoku_tab -> level_two);
    SDL_DestroyRenderer(sudoku_tab -> level_three);
    SDL_DestroyRenderer(sudoku_tab -> level_four);
    SDL_DestroyRenderer(sudoku_tab -> level_five);
    SDL_DestroyWindow(sudoku_tab -> window);
    TTF_CloseFont(sudoku_tab -> font);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}