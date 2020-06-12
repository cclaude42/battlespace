# Battlespace
Le programme qui a remporté le challenge Battlespace de 42, proposé par Geoffrey Argence (geargenc@student.42.fr)

## Le challenge

L'objectif de l'algorithme est de résoudre, en le moins de coups possible, une grille de bataille navale. Mais pas n'importe quelle bataille navale ; dans battlespace, on ne connaît pas à l'avance la forme des vaisseaux ennemis, ils peuvent être diagonaux ou carrés, et il y a des boucliers et des mines !

## Les règles et consignes

Le programme écrit sur la sortie standard son coup, type "A9", et lit sur l'entrée standard le retour, type "HIT". La grille est résolue lorsque tous les vaisseaux ont été coulés. Le code doit être en C, à la norme, et n'a accès qu'aux fonctions basiques (read, write, etc).

Pour plus d'informations, le sujet complet est dans [RULES.md](https://github.com/cclaude42/battlespace/blob/master/RULES.md).

## L'algorithme

Mon algorithme résout une grille en 57 coups en moyenne. Ce résultat est obtenu par la détermination du prochain coup, la capacité à couler un vaisseau touché, et d'autres facteurs.

### Prochain coup
Pour déterminer mon prochain coup, à chaque tour, je donne une valeur à chaque case de la grille. Ce tableau d'int de 10x10 est rempli en fonction de deux critères : état des cases voisines, et proximité au centre.

La théorie serait que si on a déjà manqué autour d'une case, il y moins de chance qu'elle cache un vaisseau. Idem pour l'emplacement, les bords de la grille ont moins de chance de cacher des vaisseaux.

Le coefficient est déterminé par [compute_coeff()](https://github.com/cclaude42/battlespace/blob/master/cclaude/coeff.c), et une fois ma grille d'ints remplies, je vise simplement la case au coefficient le plus élevé.

### La boucle
Ce tir me renverra ``MISS`` jusqu'à ce que je touche quelque chose. Je boucle donc jusqu'à avoir ``HIT``.

A chaque coup, je marque le résultat sur une grille de char de 10x10. En cas de ``BLOCKED``, je marque pour revenir plus tard. En cas de SUNK, je vérifie si j'ai coulé le bouclier. En cas de ``HIT``, je cherche à couler le vaisseau!

### Couler un vaisseau
Lorsque je touche un vaisseau, je vise les alentours jusqu'à l'avoir coulé. Je tire sur les huit cases autour de la case touchée, et si j'ai un nouveau ``HIT``, j'appelle la fonction pour couler ([sink_boat()](https://github.com/cclaude42/battlespace/blob/master/cclaude/sink.c)) en récursif. Éventuellement, toutes les cases seront touchées.

Pour optimiser le processus, je vise en priorité les lignes ou les diagonales, en fonction de l'orientation des vaisseaux que j'ai déjà touché. Je vise également les fins de lignes régulièrement ; si deux cases à la suite sont touchées, il est naturel de viser la case dans le prolongement.

Je continue jusqu'à avoir un coup bloqué (``BLOCKED``) ou avoir coulé le vaisseau (``SUNK``).

En cas de ``SUNK``, je marque les cases touchées comme coulées, et les cases autour comme manquées ; les vaisseaux ne pouvant pas être en contact, on peut être sûr qu'il n'y a rien autour. Je peux enfin retourner à ma boucle pour déterminer mon prochain coup.

### Le bouclier
À chaque tour de boucle, je vérifie les positions possibles du bouclier. Si il y en a moins de 14, je les vise jusqu'à avoir détruit le bouclier. Je vise ensuite les cases qui m'ont renvoyé ``BLOCKED``, maintenent des ``HIT`` assurés.

### Le marquage
* Ma grille de char est originellement remplie de ``.``

* En cas de ``MISS``, je marque la case d'un `` ``

* En cas de ``HIT``, je marque d'un ``x``

* En cas de ``SUNK``, je marque le vaisseau de ``o``

* Enfin, en cas de ``BLOCKED``, je marque d'un ``b``
