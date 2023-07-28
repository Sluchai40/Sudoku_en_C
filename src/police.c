#include <windows.h>
#include <fonctions.h>
#include <stdio.h>

void font_police(sudoku *sudoku_tab)
{
    TTF_Font* font = TTF_OpenFont("Kichenset.otf", FONT_SIZE);
    for (int x = 0; x < 9; x++)
    {
        char str[2];
        str[0] = x + '1';
        str[1] = 0;
        SDL_Surface* text = TTF_RenderText_Blended(font, str, (SDL_Color){ 255, 255, 255, 255});
        sudoku_tab->cellTextures[x] = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, text);
        SDL_FreeSurface(text);
    }
    TTF_CloseFont(font);
}