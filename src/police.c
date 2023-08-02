#include "fonctions.h"
#include "display.h"
#include "SDL2/SDL_image.h"

void font_police(sudoku *sudoku_tab)
{
    TTF_Font* font = TTF_OpenFont("Kichenset.otf", FONT_SIZE);
    for (int x = 0; x < 9; x++)
    {
        char str[2];
        str[0] = x + '1';
        str[1] = 0;
        SDL_Surface* text = TTF_RenderText_Blended(font, str, (SDL_Color){ 255, 255, 255, 255});
        sudoku_tab -> cellTextures[x] = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, text);
        SDL_FreeSurface(text);
        text = TTF_RenderText_Blended(font, str, (SDL_Color){255, 0, 0, 255});
        sudoku_tab -> cellTexturesPlayer[x] = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, text);
        SDL_FreeSurface(text);
    }
    TTF_CloseFont(font);
}


void end_message(sudoku *sudoku_tab)
{
    SDL_Surface* victory = TTF_RenderText_Blended(sudoku_tab -> font, "Félicitations !", (SDL_Color){ 0, 255, 0, 255});
    sudoku_tab -> victory = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, victory);
    SDL_FreeSurface(victory);
    
    SDL_Surface* loosing = TTF_RenderText_Blended(sudoku_tab -> font, "Espece de gros nul!", (SDL_Color){ 255, 0, 0, 255});
    sudoku_tab -> loosing = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, loosing);
    SDL_FreeSurface(loosing);

    SDL_Surface* font_valider = TTF_RenderText_Blended(sudoku_tab -> font, "Valider ?", (SDL_Color){255, 255, 255, 255});
    sudoku_tab -> almost_validated = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, font_valider);
    SDL_FreeSurface(font_valider);

    SDL_Surface* font_continuer = TTF_RenderText_Blended(sudoku_tab -> font, "Continuer ?", (SDL_Color){255, 255, 255, 255});
    sudoku_tab -> almost_continued = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, font_continuer);
    SDL_FreeSurface(font_continuer);

    SDL_Surface* new_game = TTF_RenderText_Blended(sudoku_tab -> font, "New Game !", (SDL_Color){255, 255, 255, 255});
    sudoku_tab -> new_game = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, new_game);
    SDL_FreeSurface(new_game);
    
    SDL_Surface* try_again = TTF_RenderText_Blended(sudoku_tab -> font, "Try Again !", (SDL_Color){255, 255, 255, 255});
    sudoku_tab -> try_again = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, try_again);
    SDL_FreeSurface(try_again);
}

void button_start(sudoku *sudoku_tab)
{
    SDL_Surface *start =  IMG_Load("press_start.jpg");
    sudoku_tab -> button_start = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, start);
    SDL_FreeSurface(start);
}

void button_finished(sudoku *sudoku_tab)
{
    SDL_Surface *finished =  IMG_Load("press_finished.png");
    sudoku_tab -> button_finished = SDL_CreateTextureFromSurface(sudoku_tab -> renderer, finished);
    SDL_FreeSurface(finished);
}