# Make it work

J'ai utilisé la library SFML dont l'instalation se fait comme suit:
```
sudo apt-get install libsfml-dev
```

Ensuite, le code compile avec
```
cd src/
make
```

Et s'execute avec
```
./casse_brique
```


# Mes fonctionnalités

## Blocs

Les blocs (ou brique) ont un "type" qui est une couleur et une solidité qui seront identiques à toute forme de bloc. Ils peuvent être déclinés via une hiérarchie vers n'importe quel forme de bloc affichable par la SFML (seul le carré est disponible).
Le conteneur est basé sur un type de bloc et 2 dimentions qui peuvent être affichés de n'importe quelle manière (en ligne, en quinconce, en rond, etc.) (seul le cadrillage est disponible et un seul est affiché au lancement du programme).

## Balle

Une balle est basé sur le même principe que les blocs au niveau du "type" qui est une couleur, une taille, et une quantité de dégâts. Les rebonds sont calculés à 4 points orthogonaux orientés en direction du potentiel mur.
Le multi balle est possible (pas implémenté en tant que bonus) avec un thread par balle. 

## Le plateau

Le plateau de déplace avec les flèches ou la souris, et garde en mémoire sa vitesse, ce qui permet de la retransmettre en partie (10%) à la balle pour lui donner un effet et changer sa direction.

## Autre fonctionnalité

Une autre fonctionnalité implémentée est la possibilité de faire pause en jeu avec la touche escape.


# Fonctionnalités non implémentés

- Pas de bonus/malus mais plusieurs pourraient être implémentés, comme le multi balle, ou les changements de taille/dégâts des blocs, balle, plateau. Également, une courbe de déplacement différente pour le plateau est possible.
- Pas de grilles variés mais l'implémentation est possible via l'héritage.
- Pas de chargement de grille depuis un fichier.

