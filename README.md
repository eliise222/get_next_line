*This project has been created as part of the 42 curriculum by elocufie*

**DESCRIPTION**
Ce projet a pour but de coder une fonction qui renvoie une ligne lue depuis un descripteur de fichier (file descriptor).

**OBJECTIFS**
- Apprendre a utiliser les variables statiques.
- Comprendre la gestion du *BUFFER*
- Maitriser l'allocation dynamique de memoire et donc eviter les leaks (fuites de memoire).
- Gerer les lectures multiples.

**FONCTIONNEMENT**
Cette fonction utilise un *BUFFER* de taille definie au moment de la compilation pour lire le fichier. Elle va stocker le "surplus" de texte qui se trouve apres la ligne dans une variable statique pour lui permettre de reprendre la lecture la ou elle s'etait arretee lorsque l'on la rappelle.

1- **La lecture** : On lit *BUFFER_SIZE* octets jusqu'a trouver un "\n" OU la fin du fichier (= EOF).
2- **Le stockage** : Concatenement de ce qui est lu dans la variable *static*
3- **Extraction** : On extrait la ligne jusqu'au premier "\n".
4- **Mise a jour** : On garde ce qui reste apres le "\n" dans la variable *static* pour le prochain appel de la fonction.

**Instructions**

*Compilation*

Pour integrer ce projeet a un programme, il faut inclure les fichiers sources et de definir la taille du tampon avec le flag *-D BUFFER_SIZE=n* :
*cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl*

*Execution*

Puisque get_next_line est une fonction et pas un programme autonome alors lorsque la compilation est faite , l'executable peut etre lance de la maniere suivante :

char *line;

while ((line = get_next_line(fd)) != NULL)
	free(line);

*Algorithme et Choix Techniques*
**-Variable Statique :** L'usage d'un tableau *static char *keep[4096]* permet de conserver les donnees lues en surplus pour chaque descripteur de fichier. Cela garantit la continuite de la lecture lors des appels successifs.

**-Lecture par blocs :** Le fichier est lu par segments de *BUFFER_SIZE*, ce qui permet d'optimiser les performances tout en restant adaptable aux contraintes.

**-Traitement du surplus :** Des qu'un "\n" est detecte , la fonction va scinder le contenu accumule. Elle va isoler la ligne qu'il faut retourner et realloue le pointeur statique pour conserver uniquement les octets restants, ce qui assure une certaine fluidite pour la lecture suivante.

*Ressources*

-comprendre ce qu'est un Buffer : https://www.journaldunet.fr/web-tech/dictionnaire-du-webmastering/1445278-buffer-definition-et-fonctionnement-pratique/

-comprendre ce qu'est une vafriable static : https://manual.gamemaker.io/beta/fr/GameMaker_Language/GML_Overview/Functions/Static_Variables.htm

comprendre le descripteur de fichier et y acceder et le manipuler : https://www.codequoi.com/manipuler-un-fichier-a-laide-de-son-descripteur-en-c/

allocation dynamique : https://zestedesavoir.com/tutoriels/755/le-langage-c-1/1043_aggregats-memoire-et-fichiers/4285_lallocation-dynamique/