*This project has been created as part of the 42 curriculum by camlalle.*

# Get Next Line

## Description
Ce projet implémente la fonction `get_next_line`, qui lit un fichier (ou un autre descripteur) et renvoie une ligne à chaque appel, y compris le caractère `\n` s’il est présent. L’objectif est de gérer la lecture par blocs avec un buffer persistant entre les appels, tout en respectant les contraintes mémoire et le comportement attendu par le sujet 42.

Le code est organisé en version standard et version bonus (multi‑FD) avec des fichiers dédiés.

## Instructions

### Compilation
- Version standard :
	- `make`
- Version bonus :
	- `make bonus`

Le `Makefile` produit une bibliothèque statique `get_next_line.a`.

### Utilisation (exemple minimal)
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
		int fd = open("example.txt", O_RDONLY);
		char *line;
		while ((line = get_next_line(fd)) != NULL)
		{
				printf("%s", line);
				free(line);
		}
		close(fd);
		return (0);
}
```

### Options de compilation
Vous pouvez définir la taille du buffer à la compilation :
`cc -D BUFFER_SIZE=42 -Wall -Wextra -Werror ...`

## Algorithme (explication et justification)
L’algorithme s’appuie sur un buffer persistant par descripteur de fichier. Le flux général est :

1. **Accumulation** : on lit par blocs de taille `BUFFER_SIZE` et on concatène le contenu dans un buffer “stock” jusqu’à rencontrer un `\n` ou la fin du fichier.
2. **Extraction de la ligne** : on découpe le buffer pour produire la ligne à renvoyer (incluant `\n` si présent).
3. **Conservation du reste** : les caractères après la ligne sont conservés pour l’appel suivant.

Justification :
- La lecture par blocs minimise les appels système `read` et respecte la contrainte du `BUFFER_SIZE` configurable.
- Le buffer persistant assure un comportement correct même si une ligne est plus longue que `BUFFER_SIZE`.
- En bonus, un tableau statique indexé par FD permet de gérer plusieurs descripteurs simultanément sans mélange de flux (`FD_MAX`).

Dans cette implémentation, `creat_buff()` lit et agrège le contenu, `updated_buff()` découpe la ligne et prépare le reste, et `get_next_line()` orchestre le tout avec gestion des cas limites (FD invalide, fin de fichier, erreurs de lecture).

## Ressources
- Documentation `read(2)` : https://man7.org/linux/man-pages/man2/read.2.html
- Règles 42 pour Get Next Line (sujet officiel)
- Tutoriel sur les buffers et la gestion de flux en C (ex. articles sur le `BUFFER_SIZE` et la lecture par blocs)

### Utilisation de l’IA
- Ce README a été rédigé avec l’aide d’un assistant IA (GitHub Copilot) pour la rédaction et la structuration du document.
