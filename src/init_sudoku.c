#include "fonctions.h"
#include <time.h>

void init_sudoku(sudoku *sudoku_tab)
{
    sudoku_tab->almost_finished = 0;
    sudoku_tab->game_finished = 0;
    sudoku_tab->time = time(NULL);
    sudoku_tab->cell_fill = 0;
    sudoku_tab->empty_cell_init = 0;

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            sudoku_tab->grid[x][y] = 0;
        }
    }
    shuffle_range(sudoku_tab);
    solver(sudoku_tab, 0, sudoku_tab->grid);
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            sudoku_tab->gridValid[x][y] = sudoku_tab->grid[x][y];
        }
    }
    remove_numbers(sudoku_tab, 10);
}