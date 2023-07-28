#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strsplit.h"
#include "fonctions.h"
#include <time.h>
#include <windows.h>


int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Usage: %s <file>\n", av[0]);
        return 1;
    }
    FILE *file = fopen(av[1], "r");
    if (!file)
    {
        printf("Error: could not open file %s\n", av[1]);
        return 1;
    }

    sudoku sudoku_tab;
    char line[1024];

    int j = 0;
    srand(time(NULL));

    while (fgets(line, sizeof(line), file))
    {
        char **tab = strsplit(line, ' ');
        for (int i = 0; tab[i]; i++)
        {
            int num = atoi(tab[i]);
            sudoku_tab.grid[j][i] = num;
            free(tab[i]);
        }
        free(tab);
        j++;
    }
    shuffle_range(&sudoku_tab);
    solver(&sudoku_tab);
    remove_numbers(&sudoku_tab, 81);
    init_graphics(&sudoku_tab);

    int isOpen = 1;

    while(isOpen)
    {
        event(&sudoku_tab, isOpen);
        SDL_Rect src = {0, 0 , GRID_SIZE, GRID_SIZE};

        SDL_SetRenderDrawColor(sudoku_tab.renderer, 156, 86, 232, 255);
        SDL_RenderClear(sudoku_tab.renderer);
        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.gridTexture, &src, &src);
        for (int x = 0; x < 9; x++)
        {
            for (int y= 0; y < 9; y++)
            {
                if (y == sudoku_tab.posY && x == sudoku_tab.posX)
                {
                    SDL_SetRenderDrawColor(sudoku_tab.renderer, 255, 255, 255, 255);
                    SDL_Rect mouse_rect = {x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE -1};
                    SDL_RenderDrawRect(sudoku_tab.renderer, &mouse_rect);
                }
                if (y == sudoku_tab.posY_clicked && x == sudoku_tab.posX_clicked)
                {
                    SDL_SetRenderDrawColor(sudoku_tab.renderer, 254, 70, 165, 255);
                    SDL_Rect mouse_rect = {x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1};
                    SDL_RenderFillRect(sudoku_tab.renderer, &mouse_rect);
                }
                SDL_Rect test = {y * CELL_SIZE + CELL_MARGIN, x * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};
                if (sudoku_tab.grid[x][y] != 0)
                {
                    SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.cellTextures[sudoku_tab.grid[x][y] - 1], NULL, &test);    
                }
            }
        }
        SDL_RenderPresent(sudoku_tab.renderer);
    }
    quitGraphics(&sudoku_tab);
    return 0;
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	hInst = hInst;
	hInstPrev = hInstPrev;
	cmdshow = cmdshow;

	int ac = 1;
	char **av = NULL;

	char exePath[MAX_PATH];
	GetModuleFileName(NULL, exePath, MAX_PATH);
	av = realloc(av, sizeof(char *) * (ac));
	av[0] = exePath;
	char *token = strtok(cmdline, " ");

	while (token != NULL)
	{
		av = realloc(av, sizeof(char *) * (ac + 1));
		av[ac] = token;
		ac++;
		token = strtok(NULL, " ");
	}

	int result = main(ac, av);

	free(av);
	fclose(stdout);
	FreeConsole();

	return result;
}