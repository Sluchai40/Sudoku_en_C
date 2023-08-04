#include "fonctions.h"
#include "display.h"

#include "SDL2/SDL_image.h"

void cat_sprite(sudoku *sudoku_tab)
{
    SDL_Surface *cat_sprite = IMG_Load("animatedcat.png");
    sudoku_tab -> cat_sprite = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, cat_sprite);
    SDL_FreeSurface(cat_sprite);
}

void animated_cat (sudoku *sudoku_tab, int y)
{
    int pixel = 530 * ((sudoku_tab -> count / 250) %10);
    SDL_Rect cat_source = {pixel, 0, 532, 374};
    SDL_Rect cat_destination = {LEVEL_SIZE - CELL_SIZE , y, CELL_SIZE * 2, CELL_SIZE * 1.5};
    SDL_RenderCopy(sudoku_tab -> renderer, sudoku_tab -> cat_sprite, &cat_source, &cat_destination);
}