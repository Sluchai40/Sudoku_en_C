#include "fonctions.h"
#include "strsplit.h"
#include "display.h"

void event(sudoku *sudoku_tab, int *isOpen)
{
    SDL_Event events;

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_MOUSEMOTION:
            sudoku_tab->posX = events.motion.x / CELL_SIZE;
            sudoku_tab->posY = events.motion.y / CELL_SIZE;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                sudoku_tab->posX_clicked = sudoku_tab->posX;
                sudoku_tab->posY_clicked = sudoku_tab->posY;
                const SDL_Point point_click = {events.motion.x, events.motion.y};
                const SDL_Rect rect_button = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 8, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect valider = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3.5, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect continuer = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 4.5, CELL_SIZE * 2, CELL_SIZE};
                if (SDL_PointInRect(&point_click, &rect_button) == SDL_TRUE)
                {
                    init_sudoku(sudoku_tab);
                }
                if (sudoku_tab->almost_finished == 1 && SDL_PointInRect(&point_click, &valider) == SDL_TRUE)
                {
                    if (test_fin(sudoku_tab))
                    {
                        sudoku_tab->game_finished = 1;
                    }
                    else
                    {
                        sudoku_tab->game_finished = 2;
                    }
                    if (sudoku_tab->almost_finished == 1 && SDL_PointInRect(&point_click, &continuer) == SDL_TRUE)
                    {
                        sudoku_tab->grid[sudoku_tab->last_y_position][sudoku_tab->last_x_position] = 0;
                        sudoku_tab->cell_fill--;
                        sudoku_tab->almost_finished = 0;
                    }
                }
            }
            break;

        case SDL_KEYDOWN:
            if (events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9)
            {
                if (sudoku_tab->grid[sudoku_tab->posY][sudoku_tab->posX] == 0)
                {
                    sudoku_tab->grid[sudoku_tab->posY_clicked][sudoku_tab->posX_clicked] = events.key.keysym.sym - SDLK_0;
                    sudoku_tab->cell_fill++;
                    // sudoku_tab->last_x_position = sudoku_tab->posX_clicked;
                    // sudoku_tab->last_y_position = sudoku_tab->posY_clicked;
                    int x, y;
                    if (!case_vide(sudoku_tab->grid, &x, &y))
                    {
                        sudoku_tab->almost_finished = 1;
                    }
                }
            }
            if (events.key.keysym.scancode == SDL_SCANCODE_DELETE || events.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
            {
                if (sudoku_tab->gridClone[sudoku_tab->posY_clicked][sudoku_tab->posX_clicked] == 0)
                {
                    sudoku_tab->grid[sudoku_tab->posY_clicked][sudoku_tab->posX_clicked] = 0;
                    sudoku_tab->cell_fill--;
                }
            }
            if (events.key.keysym.sym == SDLK_SPACE)
            {
                init_sudoku(sudoku_tab);
            }
            break;
        case SDL_QUIT:
            *isOpen = 0;
            break;
        }
    }
}