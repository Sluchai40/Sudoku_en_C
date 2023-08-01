#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strsplit.h"
#include "fonctions.h"
#include <time.h>
#include <windows.h>
#include "display.h"

#include "SDL2/SDL_image.h"


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
    // shuffle_range(&sudoku_tab);
    // solver(&sudoku_tab, 0, sudoku_tab.grid);
    // remove_numbers(&sudoku_tab, 81);
    init_graphics(&sudoku_tab);

    int isOpen = 1;

    while(isOpen)
    {
        event(&sudoku_tab, &isOpen);

        SDL_Rect src = {0, 0 , GRID_SIZE + 1, GRID_SIZE};

        SDL_SetRenderDrawColor(sudoku_tab.renderer, 156, 86, 232, 255);
        SDL_RenderClear(sudoku_tab.renderer);

        SDL_Rect rect_button_start = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 8, CELL_SIZE * 2, CELL_SIZE};
        SDL_SetRenderDrawColor(sudoku_tab.renderer, 156, 86, 232, 255);
        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.button_start, NULL, &rect_button_start);

        SDL_Rect rect_button_finished = {GRID_SIZE + CELL_SIZE, 0, CELL_SIZE * 2, CELL_SIZE};
        SDL_SetRenderDrawColor(sudoku_tab.renderer, 156, 86, 232, 255);
        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.button_finished, NULL, &rect_button_finished);

        const int line_max_height = CELL_SIZE * 7;
        int line_height = line_max_height * sudoku_tab.cell_fill /sudoku_tab.empty_cell_init;
        SDL_Rect rect_jauge_progression = {(GRID_SIZE + MENU_SIZE / 2) - 2, CELL_SIZE * 8 - line_height, 5, line_height};
        SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(sudoku_tab.renderer, &rect_jauge_progression);

        if (sudoku_tab.game_finished == 0)
        {
            time_t time_frame = time(NULL);
            unsigned long long int t = difftime(time_frame, sudoku_tab.time);
            struct tm * time_info;
            char timeString[9];
            time_info = localtime(&t);
            strftime(timeString, sizeof(timeString), "%M,%S", time_info);
            SDL_Surface* time_clock = TTF_RenderText_Blended(sudoku_tab.font, timeString, (SDL_Color){ 0, 0, 0, 255});
            SDL_Texture* time_clock_texture = SDL_CreateTextureFromSurface(sudoku_tab.renderer, time_clock);

            SDL_Rect time_clock_rect = {GRID_SIZE + CELL_SIZE + 4, 0 + CELL_SIZE / 2, CELL_SIZE * 2 - 8, CELL_SIZE / 2};
            SDL_RenderCopy(sudoku_tab.renderer, time_clock_texture, NULL, &time_clock_rect);

            SDL_FreeSurface(time_clock);
            SDL_DestroyTexture(time_clock_texture);
        }

        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.gridTexture, &src, &src);
        for (int x = 0; x < 9; x++)
        {
            for (int y= 0; y < 9; y++)
            {
                if (x == sudoku_tab.posY && y == sudoku_tab.posX)
                {
                    SDL_SetRenderDrawColor(sudoku_tab.renderer, 255, 255, 255, 255);
                    SDL_Rect mouse_rect = {y * CELL_SIZE + 1, x * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE -1};
                    SDL_RenderDrawRect(sudoku_tab.renderer, &mouse_rect);
                }
                if (x == sudoku_tab.posY_clicked && y == sudoku_tab.posX_clicked)
                {
                    SDL_SetRenderDrawColor(sudoku_tab.renderer, 254, 70, 165, 255);
                    SDL_Rect mouse_rect = {y * CELL_SIZE + 1, x * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1};
                    SDL_RenderFillRect(sudoku_tab.renderer, &mouse_rect);
                }
                SDL_Rect test = {y * CELL_SIZE + CELL_MARGIN, x * CELL_SIZE + CELL_MARGIN, FONT_SIZE, FONT_SIZE};
                if (sudoku_tab.grid[x][y] != 0)
                {
                    SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.cellTextures[sudoku_tab.grid[x][y] - 1], NULL, &test);    
                }
            }
        }
        if (sudoku_tab.almost_finished == 1)
        {
            SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 0, 0, 255);
            SDL_Rect valider = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3.5, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &valider);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.almost_finish, NULL, &valider);

        }
        if (sudoku_tab.game_finished == 1)
        {
            SDL_Rect end_message = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, FONT_SIZE};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.victory, NULL, &end_message);
        }
        if (sudoku_tab.game_finished == 2)
        {
            SDL_Rect end_message = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, FONT_SIZE};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.loosing, NULL, &end_message);
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