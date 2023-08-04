# Présentation d'un projet de Sudoku en C

## Objectif : Réussir en 3 semaines en partant d'une base de quasiment 0 à coder un Sudoku en C.

### Merci à rle-ru (https://github.com/rle-ru) (ne vous fiez pas à son git; cette homme est une machine de guerre !) et clement-caillat notre formateur durant ces 3 mois et demi à La_Plateforme pour la formation AWS (https://github.com/clement-caillat) nos senseï qui nous ont accompagnés durant ces 3 semaines.
### Projet réalisé en collaboration avec Dhjali ma binôme pour les 3 prochaines années de formations (si elle me supporte jusque là) (https://github.com/Dhjali).

Première étape construction d'une grille:

![Grille avec de superbe couleur.](Grille_de_sudoku.png)

Viens ensuite la génération d'un sudoku valide:

![Génération d'un sudoku en brut force](Generation_Sudoku.png)

Nous avons passé quelques temps à faire de l'algorithmie afin de faire un Sudoku plus "humain" vous trouverez ces quelques "merveilles" dans le dossier Solver_humain en voilà l'exemple le plus simple:

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

Afin que le générateur de Sudoku soit efficace il nous aurait fallu faire 7, 8 voir 9 fonctions différentes et par manque de temps nous avons décidé de repasser sur le rendu visuel et nous sommes laissé emporter par notre imagination.En voici quelques features:

![Prêt au départ, des flammes et un chat](feature.png)

Bien sûr le résultat final n'est pas parfait mais le but était bien de s'en tenir aux 3 semaines et pas une minute de plus. En ce qui concerne la charte graphique je suis particulièrement fière de mes choix. Je précise que ma binôme à beaucoup moins de gout.

A bientôt pour de nouvelles aventures spatiales...


