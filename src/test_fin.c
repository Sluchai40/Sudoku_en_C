#include "fonctions.h"
#include "strsplit.h"

int test_fin(sudoku *sudoku_tab)
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (sudoku_tab -> grid[x][y] != sudoku_tab -> gridValid [x][y])
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}