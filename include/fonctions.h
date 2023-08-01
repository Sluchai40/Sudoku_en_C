#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct s_sudoku
{
    SDL_Window      *window;
	SDL_Renderer    *renderer;
	SDL_Texture     *gridTexture;
	SDL_Texture     *cellTextures[9];
    SDL_Texture     *victory;
    SDL_Texture     *loosing;
    SDL_Texture     *button_start;
    SDL_Texture     *button_finished;
    TTF_Font        *font;

    int             range[9];
    int             grid[9][9];
    int             gridValid[9][9];
    int             gridClone[9][9];
    int             gridass[9][9][9];

    int             posX;
    int             posY;
    int             posX_clicked;
    int             posY_clicked;
    int             game_finished;

    time_t          time;

}                   sudoku;

/*
**  Trouve une case vide
*/
int case_vide(int grid[9][9], int *x, int *y);

int test_chiffre(int n, int grid[9][9], int x, int y);

int solver(sudoku *sudoku_tab, int count, int grid[9][9]);

void shuffle_range(sudoku *sudoku_tab);

void remove_numbers(sudoku *sudoku_tab, int clean_numb);

int idiot_solver(sudoku *sudoku_tab);

int gridass (sudoku *sudoku_tab);

int celib_nu (sudoku *sudoku_tab);

int celib_cache (sudoku *sudoku_tab);

int segment (sudoku *sudoku_tab);

int segment_2(sudoku *sudoku_tab);

void init_graphics(sudoku *sudoku_tab);

void init_grid_surface(sudoku *sudoku_tab);

void quitGraphics(sudoku *sudoku_tab);

void font_police(sudoku *sudoku_tab);

void event (sudoku *sudoku_tab, int *isOpen);

void init_sudoku(sudoku *sudoku_tab);

int test_fin(sudoku *sudoku_tab);

void end_message(sudoku *sudoku_tab);

void button_start(sudoku *sudoku_tab);

void button_finished(sudoku *sudoku_tab);

#endif