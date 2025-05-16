# Corewar

## Description
Le principe du projet COREWAR est de compiler plusieurs fichier, qui s'apparentent à des robots dans une arène.
Ce projet a été réalisé en C, en respectant les contraintes imposées par les normes d'EPITECH et les attentes du projet.  

## Compilation

### Prérequis
Avant de compiler le projet, assurez-vous d'avoir les outils suivants installés :
- GCC
- Make

### Instructions
1. Clonez le dépôt sur votre machine :
   `git clone git@github.com:Leo-Batilliot/Corewar.git`

2. Accédez au répertoire du projet :
   `cd Epitech`

3. Compilez le projet avec la commande suivante :
   `make`

4. L'exécutable sera généré sous le nom `corewar`.

5. Pour nettoyer les fichiers objets générés lors de la compilation :
   `make clean`

6. Pour supprimer tous les fichiers générés, y compris l'exécutable :
   `make fclean`

7. Pour nettoyer et recompiler le projet :
   `make re`

### Exemple d'utilisation

Après avoir compilé le projet, vous pouvez lancer 42sh en exécutant la commande `./corewar [options] file1.cor [file2.cor ...]`
Vous avez à disponibilités plusieurs flags possible:

-dump : affiche la mémoire au bout de N cycles
-n : définit l’ID du joueur suivant
-a : load le champion à une adresse dans l'arène, par défaut leurs placement sont optimisés

## Fonctionnalités

Pour compiler vous devez créer un fichier .cor avec l'executable donné.
./asm ficher.s

Dans ce fichier vous devez créer un petit code dans un language très simple, exemple typique:

#
.name "Abel"
.comment "L'amer noir."

sti r1, %:hi, %1

hi:	live %1
	ld %0, r3
	zjmp %:hi
#

Des exemples plus concrets seront dispoinble sur le repo.

## Commandes:
voici toutes les commandes:

- live
- ld
- st
- add
- sub
- and
- or
- xor
- zjmp
- ldi
- sti
- fork
- lld
- lldi
- lfork
- aff

### BONUS:

## Structure du Code

### Structures des dossiers :

- `include` :  Contient les fichiers .h contenant les définitions de fonctions, de structures et les define.  
- `lib` : Contient les fonctions utilitaires (souvent recodées et modifiées) pour de divers projets.  
- `src/` : Contient le main et les dossiers principaux du projet
- `src/utils/` : Contient des fonctions utilitaires pour le projet
- `src/cmd/` : Contient toutes les fonctions des commandes

### Documentation

Les fonctions sont documentées de la manière suivante :
```
// nom :   nom_de_fonction
// arguments :   arguments + explications (les arguments peuvent etre N.A si il n'y a pas d'arguments)
// fonctionnalité : explications (peut etre S.E (self explanatory) si le nom de fonction est assez clair)
type_de_fonction nom_de_fonction (arguments)
```


###
MADE BY:
Gabin Wilson
Léo Batillot
