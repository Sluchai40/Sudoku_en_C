#include "fonctions.h"
#include <time.h>

void init_sudoku(sudoku *sudoku_tab)
{
    sudoku_tab -> game_finished = 0;
    sudoku_tab -> time = time(NULL);
    
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
            sudoku_tab -> gridValid[x][y] = sudoku_tab ->grid[x][y];
        }
    }
    remove_numbers(sudoku_tab, 5);
}