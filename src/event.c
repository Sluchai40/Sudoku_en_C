#include "fonctions.h"
#include "strsplit.h"

void event (sudoku *sudoku_tab, int *isOpen)
{
    SDL_Event events;

    while (SDL_PollEvent(&events))
    {
        switch(events.type)
        {
            case SDL_MOUSEMOTION:
                sudoku_tab -> posX = events.motion.x / CELL_SIZE;
                sudoku_tab -> posY = events.motion.y / CELL_SIZE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                {
                    sudoku_tab -> posX_clicked = sudoku_tab -> posX;
                    sudoku_tab -> posY_clicked = sudoku_tab -> posY;
                }
                break;

            case SDL_KEYDOWN:
                if(events.key.keysym.sym >= SDLK_1 && events.key.keysym.sym <= SDLK_9)
                {
                    if (sudoku_tab -> grid[sudoku_tab -> posY][sudoku_tab -> posX] == 0)
                    {
                        sudoku_tab -> grid[sudoku_tab -> posY_clicked][sudoku_tab ->posX_clicked] = events.key.keysym.sym - SDLK_0;
                        int x, y;
                        if (!case_vide(sudoku_tab -> grid, &x, &y))
                        {
                            if (test_fin(sudoku_tab))
                            {
                                sudoku_tab -> game_finished = 1;
                            }
                            else
                            {
                                sudoku_tab -> game_finished = 2;
                            }
                        }
                    }
                }
                if(events.key.keysym.scancode == SDL_SCANCODE_DELETE || events.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                {
                    if (sudoku_tab -> gridClone[sudoku_tab -> posY_clicked][sudoku_tab -> posX_clicked] == 0)
                    {
                        sudoku_tab -> grid[sudoku_tab -> posY_clicked][sudoku_tab -> posX_clicked] = 0;
                    }
                }
                if(events.key.keysym.sym == SDLK_SPACE)
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