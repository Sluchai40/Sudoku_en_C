#include <windows.h>
#include <fonctions.h>

void init_graphics(sudoku *sudoku_tab)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    sudoku_tab -> window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    sudoku_tab -> renderer = SDL_CreateRenderer(sudoku_tab -> window, -1, SDL_RENDERER_ACCELERATED);
    sudoku_tab -> font = TTF_OpenFont("Kichenset.otf", FONT_SIZE * 2);
    init_grid_surface(sudoku_tab);
    font_police(sudoku_tab);
    end_message(sudoku_tab);
    sudoku_tab->posX = 0;
    sudoku_tab->posY = 0;
    sudoku_tab->posX_clicked = 0;
    sudoku_tab->posY_clicked = 0;
}