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

    init_graphics(&sudoku_tab);

    int isOpen = 1;
    while (isOpen)
    {
        event(&sudoku_tab, &isOpen);

        SDL_Rect src = {0, 0, GRID_SIZE + 1, GRID_SIZE};

        SDL_SetRenderDrawColor(sudoku_tab.renderer, 156, 86, 232, 255);
        SDL_RenderClear(sudoku_tab.renderer);
        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.gridTexture, &src, &src);

        if (sudoku_tab.almost_starting == 0)
        {
            SDL_Rect rect_button_start = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 7.5, CELL_SIZE * 2, CELL_SIZE * 1.5};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.button_start, NULL, &rect_button_start);
            SDL_Rect rect_button_finished = {GRID_SIZE + CELL_SIZE, 0, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.button_finished, NULL, &rect_button_finished);
        }
        
        if (sudoku_tab.almost_starting == 1)
        {
            SDL_Rect level_one = {LEVEL_SIZE - 25, GRID_SIZE - 50, 50, 50};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.level_one, NULL, &level_one);
            SDL_Rect level_two = {LEVEL_SIZE - 35, GRID_SIZE - 120, 70, 70};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.level_two, NULL, &level_two);
            SDL_Rect level_three = {LEVEL_SIZE - 45, GRID_SIZE - 210, 90, 90};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.level_three, NULL, &level_three);
            SDL_Rect level_four = {LEVEL_SIZE - 55, GRID_SIZE - 320, 110, 110};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.level_four, NULL, &level_four);
            SDL_Rect level_five = {LEVEL_SIZE - 65, 0, 130, 130};
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.level_five, NULL, &level_five);

        }

        const int line_max_height = CELL_SIZE * 6.5;
        int line_height = line_max_height * sudoku_tab.cell_fill / sudoku_tab.empty_cell_init;
        SDL_Rect rect_jauge_progression = {(GRID_SIZE + MENU_SIZE / 2) - 2, CELL_SIZE * 7.5 - line_height, 5, line_height};
        SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(sudoku_tab.renderer, &rect_jauge_progression);

        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                if (x == sudoku_tab.posY && y == sudoku_tab.posX)
                {
                    SDL_SetRenderDrawColor(sudoku_tab.renderer, 255, 255, 255, 255);
                    SDL_Rect mouse_rect = {y * CELL_SIZE + 1, x * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1};
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
                    if (sudoku_tab.gridClone[x][y] != 0)
                    {
                        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.cellTextures[sudoku_tab.grid[x][y] - 1], NULL, &test);
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 255, 0, 255);
                        SDL_RenderFillRect(sudoku_tab.renderer, &test);
                        SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.cellTexturesPlayer[sudoku_tab.grid[x][y] - 1], NULL, &test);
                    }
                }
            }

        if (sudoku_tab.game_finished == 0)
        {
            time_t time_frame = time(NULL);
            unsigned long long int t = difftime(time_frame, sudoku_tab.time);
            struct tm *time_info;
            char timeString[9];
            time_info = localtime((time_t*)&t);
            strftime(timeString, sizeof(timeString), "%M,%S", time_info);
            SDL_Surface *time_clock = TTF_RenderText_Blended(sudoku_tab.font, timeString, (SDL_Color){0, 0, 0, 255});
            SDL_Texture *time_clock_texture = SDL_CreateTextureFromSurface(sudoku_tab.renderer, time_clock);

            SDL_Rect time_clock_rect = {GRID_SIZE + CELL_SIZE + 4, 0 + CELL_SIZE / 2, CELL_SIZE * 2 - 8, CELL_SIZE / 2};
            SDL_RenderCopy(sudoku_tab.renderer, time_clock_texture, NULL, &time_clock_rect);

            SDL_FreeSurface(time_clock);
            SDL_DestroyTexture(time_clock_texture);
        }

        if (sudoku_tab.almost_finished == 1 && sudoku_tab.game_finished == 0)
        {
            SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 0, 0, 255);

            SDL_Rect valider = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &valider);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.almost_validated, NULL, &valider);

            SDL_Rect continuer = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 5, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &continuer);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.almost_continued, NULL, &continuer);
        }

        if (sudoku_tab.game_finished == 1)
        {
            SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 0, 0, 255);

            SDL_Rect end_message = {0, CELL_SIZE * 4, GRID_SIZE, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &end_message);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.victory, NULL, &end_message);

            SDL_Rect new_game = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &new_game);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.new_game, NULL, &new_game);

            SDL_Rect try_again = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 5, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &try_again);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.try_again, NULL, &try_again);
        }
        if (sudoku_tab.game_finished == 2)
        {
            SDL_SetRenderDrawColor(sudoku_tab.renderer, 0, 0, 0, 255);

            SDL_Rect end_message = {0, CELL_SIZE * 4, GRID_SIZE, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &end_message);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.loosing, NULL, &end_message);

            SDL_Rect new_game = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 3, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &new_game);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.new_game, NULL, &new_game);

            SDL_Rect try_again = {GRID_SIZE + CELL_SIZE, CELL_SIZE * 5, CELL_SIZE * 2, CELL_SIZE};
            SDL_RenderFillRect(sudoku_tab.renderer, &try_again);
            SDL_RenderCopy(sudoku_tab.renderer, sudoku_tab.try_again, NULL, &try_again);
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