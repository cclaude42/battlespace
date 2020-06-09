# Battlespace
Le programme qui a remporté le challenge Battlespace de 42, proposé par Geoffrey Argence (geargenc@student.42.fr)

## Le challenge

L'objectif de l'algorithme est de résoudre, en le moins de coups possible, une grille de bataille navale. Mais pas n'importe quelle bataille navale ; dans battlespace, on ne connaît pas à l'avance la forme des bateaux ennemis, les bateaux peuvent être en diagonale, et il y a des boucliers et des mines !


## Les règles et consignes

Le programme écrit sur la sortie standard son coup, type "A9", et lit sur l'entrée standard le retour, type "HIT". La grille est résolue lorsque tous les bateaux ont été coulés. Le code doit être en C, à la norme, et n'a accès qu'aux fonctions basiques (read, write, etc).

Pour plus d'informations, le sujet complet est dans RULES.md.

## L'algorithme

Mon algorithme résout une grille en 57 coups en moyenne. Ce résultat est obtenu par la détermination du prochain coup, la capacité à couler un bateau touché, et d'autres facteurs.

### Prochain coup
Pour déterminer mon prochain coup, à chaque tour, je donne une valeur à chaque case de la grille. Ce tableau d'int de 10x10 est rempli en fonction de deux critères : état des cases voisines, et proximité au centre.

La théorie serait que si on a déjà manqué autour d'une case, il y moins de chance qu'elle cache un bateau. Idem pour l'emplacement, les bords de la grille ont moins de chance de cacher des bateaux.

Le coefficient est déterminé par compute_coeff (coeff.c), et une fois ma grille d'ints remplies, je vise simplement la case au coefficient le plus élevé.

### La boucle
Ce tir me renverra MISS jusqu'à ce que je touche quelque chose. Je boucle donc jusqu'à avoir HIT.

A chaque coup, je marque le résultat sur une grille de char de 10x10. En cas de BLOCKED, je marque pour revenir plus tard. En cas de SUNK, je vérifie si j'ai coulé le bouclier. En cas de HIT, je cherche à couler le bateau!

### Couler un bateau
[TO BE DONE]
