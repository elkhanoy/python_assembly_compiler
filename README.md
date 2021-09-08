# README Projet informatique SEI SICOM 2021

## Rappel sur les rendus
Les rendus de chaque incrément et le rendu final sont attendus sur Git.

C'est l'état du dépôt sur le serveur à la date du rendu qui fait foi.

Aucun rendu par mail !

Votre code doit fonctionner sur les machines Phelma ou sur la machine virtuelle Phelma 2020-21.



## Contenu attendu pour votre dépot Git

Dans tous les cas, votre dépôt Git devra contenir a minima :
* un fichier README.md à la racine (ce fichier, à mettre à jour), qui explique brièvement comment compiler, comment exécuter, comment tester
* un fichier Makefile qui permet de compiler avec la commande make
* votre code source, organisé en sous-répertoires
* tous vos programmes principaux de test et les informations indiquant tous les tests que vous avez réalisés
* les autres fichiers nécessaires au fonctionnement de votre projet - typiquement le fichier de description des lexèmes, etc.
* vos rapports (un par incrément), au format PDF

A l'inverse, un dépôt Git ne doit PAS contenir :
* les fichiers binaires objet .o et les binaires exécutables : ils sont régénérés à chaque fois !

Le fichier .gitignore fourni à la racine du dépôt permet déjà que tous les fichiers objet .o ou et tous les fichiers d'extension .exe soient ignorés par Git. Vous pouvez modifier / étendre ce fichier si besoin.

## Structure typique du dépôt

Nous conseillons de vous inspirer de l'arborescence suivante pour votre dépot git :

```bash
Racine du dépôt Git
  |_ .gitignore : le fichier <gitignore>
  |_ README.md : ce README (à mettre à jour !)
  |_ Makefile : votre fichier Makefile, qui doit permettre de tout compiler facilement (exécutable final, tests...)
  |_ include
     |_ tous les fichiers header .h, éventuellement organisés dans des sous-répertoires
  |_ src    
     |_ tous les fichiers source .c (sauf les programmes principaux)
  |_ tests
     |_  les fichiers source .c de tous les main de test
     |_  les données nécessaires aux tests
  |_ rapports
     |_ Les rapports de chaque incrément et le rapport final
```
