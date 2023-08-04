# Présentation d'un projet de Sudoku en C

## Objectif : Réussir en 3 semaines en partant d'une base de quasiment 0 à coder un Sudoku en C.

### Merci à rle-ru et clement-caillat nos senseï qui nous ont accompagnés durant ces 3 semaines.
### Projet réalisé en collaboration avec Dhjali

Première étapes notre construction d'une grille:

![Grille avec de superbe couleur.](Grille_de_sudoku.png)

Viens ensuite la génération d'un soduku valide:

![Génération d'un sudoku en brut force](Generation_Sudoku.png)

Nous avons passé quelque temps a faire de l'alorythmie afin de faire un Sudoku plus "humain" vous trouverez ces quelques "merveilles" dans le dossier Solver_humain en voilà l'exemple le plus simple:

```
int celib_nu(sudoku *sudoku_tab)
{
    int collect_true;
    int last;
    int return_value = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku_tab->gridClone[i][j] == 0)
            {
                collect_true = 0;

                for (int n = 1; n < 10; n++)
                {
                    if (sudoku_tab->gridass[i][j][n - 1] == TRUE)
                    {
                        collect_true++;
                        last = n;
                    }
                }
                if (collect_true == 1)
                {
                    sudoku_tab->gridClone[i][j] = last;
                    return_value++;
                }
            }
        }
    }
    return return_value;
}
```

