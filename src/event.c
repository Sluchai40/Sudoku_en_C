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
                SDL_Rect valider = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect continuer = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 5, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect new_game = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect try_again = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 5, CELL_SIZE * 2, CELL_SIZE};
                SDL_Rect level_one = {LEVEL_SIZE - 25, GRID_SIZE - 50, 50, 50};
                SDL_Rect level_two = {LEVEL_SIZE - 35, GRID_SIZE - 120, 70, 70};
                SDL_Rect level_three = {LEVEL_SIZE - 45, GRID_SIZE - 210, 90, 90};
                SDL_Rect level_four = {LEVEL_SIZE - 55, GRID_SIZE - 320, 110, 110};
                SDL_Rect level_five = {LEVEL_SIZE - 65, 0, 130, 130};

                if (SDL_PointInRect(&point_click, &level_one) == SDL_TRUE && sudoku_tab -> almost_starting == 1)
                {
                    sudoku_tab -> clean_number = 15;
                    init_sudoku(sudoku_tab);
                    sudoku_tab -> almost_starting = 2;
                }

                if (SDL_PointInRect(&point_click, &level_two) == SDL_TRUE && sudoku_tab -> almost_starting == 1)
                {
                    sudoku_tab -> clean_number = 30;
                    init_sudoku(sudoku_tab);
                    sudoku_tab -> almost_starting = 2;
                }

                if (SDL_PointInRect(&point_click, &level_three) == SDL_TRUE && sudoku_tab -> almost_starting == 1)
                {
                    sudoku_tab -> clean_number = 45;
                    init_sudoku(sudoku_tab);
                    sudoku_tab -> almost_starting = 2;
                }

                if (SDL_PointInRect(&point_click, &level_four) == SDL_TRUE && sudoku_tab -> almost_starting == 1)
                {
                    sudoku_tab -> clean_number = 60;
                    init_sudoku(sudoku_tab);
                    sudoku_tab -> almost_starting = 2;
                }

                if (SDL_PointInRect(&point_click, &level_five) == SDL_TRUE && sudoku_tab -> almost_starting == 1)
                {
                    sudoku_tab -> clean_number = 75;
                    init_sudoku(sudoku_tab);
                    sudoku_tab -> almost_starting = 2;
                }

                if (SDL_PointInRect(&point_click, &rect_button) == SDL_TRUE && sudoku_tab -> almost_starting == 0)
                {
                    sudoku_tab -> almost_starting = 1;
                }

                if (sudoku_tab -> game_finished > 0 && SDL_PointInRect(&point_click, &new_game) == SDL_TRUE)
                {
                    sudoku_tab -> almost_starting = 1;
                }

                if (sudoku_tab -> game_finished > 0 && SDL_PointInRect(&point_click, &try_again) == SDL_TRUE)
                {
                    sudoku_tab -> cell_fill = 0;
                    sudoku_tab -> game_finished = 0;
                    sudoku_tab -> almost_finished = 0;
                    sudoku_tab -> time = time(NULL);

                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            sudoku_tab->grid[i][j] = sudoku_tab->gridClone[i][j];
                        }
                    }
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
                }

                if (sudoku_tab->almost_finished == 1 && SDL_PointInRect(&point_click, &continuer) == SDL_TRUE)
                {
                    sudoku_tab->grid[sudoku_tab->last_y_position][sudoku_tab->last_x_position] = 0;
                    sudoku_tab->cell_fill--;
                    sudoku_tab->almost_finished = 0;
                }
                if (sudoku_tab -> almost_starting == 2)
                {
                    sudoku_tab -> almost_starting = 0;
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
                    sudoku_tab->last_x_position = sudoku_tab->posX_clicked;
                    sudoku_tab->last_y_position = sudoku_tab->posY_clicked;
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