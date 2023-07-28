#include "fonctions.h"

void event (sudoku *sudoku_tab, int *isOpen)
{
    SDL_Event events;
    int posX_clicked;
    int posY_clicked;

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
                    }
                }
                if(events.key.keysym.scancode == SDL_SCANCODE_DELETE || events.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                {
                    if (sudoku_tab -> grid[sudoku_tab -> posY][sudoku_tab -> posX] == 0)
                    {
                    sudoku_tab -> grid[sudoku_tab -> posY_clicked][sudoku_tab -> posX_clicked] = 0;
                    }
                }
                break;
            case SDL_QUIT:
                *isOpen = 0;
                break;
        }
    }
}