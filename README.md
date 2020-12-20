***Hello World, Pour une explication plus détaillé, on recommande l'analyses des deux fichiers: celui de [l'énancé du problèm](https://github.com/Me-WM/miniProject_ER_Interpreter/blob/main/Mini-Projet.pdf/) et notre [rapport](https://github.com/Me-WM/miniProject_ER_Interpreter/blob/main/Mini-Project%20-%20Rapport.pdf/)***

# Interpréteur pour les expressions régulières sur l’alphabet A = {a, b}

L’objectif de ce mini projet est la réalisation (en Flex et Bison) d’un interpréteur pour les expressions régulières sur l’alphabet A = {a, b}. Cet interpréteur assure un ensemble d’opérations, on note une petite partie :
```
• vérifier si une expression tapée est une expression régulière valide ;
• calculer la taille d’une telle expression ;
• représenter en mémoire une expression régulière sous la forme d’un AST ;
• afficher l’AST d’une expression régulière ;
• calculer l’AST du résiduel d’une expression régulière ;
• tester si le langage dénoté par une expression régulière contient le mot vide, contient
un mot donné, est vide, fini, infini, est un simple symbole, ou est réduit à un seul mot ;
```
On rappelle qu’un ***AST*** (***arbre de syntaxe abstrait*** en Français et ***Abstract Syntax Tree*** en Anglais) est une représentation réduite de l’arbre de dérivation : il ne stocke que les éléments necéssaires à l’analyse sémantique. Votre analyseur syntaxique produira un ***AST***
dont les nœuds sont définis par la structure suivante :

``` C
struct ast
{
enum { CONCAT, UNION, ETOILE, A, B, EPSILON, VIDE } type;
struct ast *fg; /* fils gauche */
struct ast *fd; /* fils droit */
};
```


Le champ type indique le type de l’opération dans l’expression régulière. Si le type d’un nœud est **ETOILE**, le champ *fd* doit être à *NULL* ; si c’est A, B, **EPSILON** ou **VIDE**, alors *fg* et *fd* sont tous les deux à *NULL*.

Le Code source est un peu volumineux, pour cela il est distribué sur quatre fichiers
sources :
>[par.y](https://github.com/Me-WM/miniProject_ER_Interpreter/par.y/) : qui va contenir le code Bison de l’analyseur syntaxique ;

>[sca.lex](https://github.com/Me-WM/miniProject_ER_Interpreter/sca.lex/) : qui va contenir le code Flex de l’analyseur lexical ;

>[ast.h](https://github.com/Me-WM/miniProject_ER_Interpreter/ast.h/) : qui va contenir les structures de données et les routines nécessaires pour la création et la manipulation des arbres abstraits ;

>[ast.c](https://github.com/Me-WM/miniProject_ER_Interpreter/ast.c/) : qui va contenir la définition de ces routines (le code C) ;


## Explication des routines utilisées dans le programme
On a bien noté que le fichier « ast.c » contient la définition de ces routines (le code C).
Pour une explication plus détaillé sur l’algorithme utilisé pour chaque fonction et la façons d'utiliser l'application.
On recomende de voir le rapport complet [Mini-Project - Rapport.pdf](https://github.com/Me-WM/miniProject_ER_Interpreter/blob/main/Mini-Project%20-%20Rapport.pdf/)

![firstView](https://github.com/Me-WM/miniProject_ER_Interpreter/blob/main/ScreenShot/Screenshot%20from%202015-02-09%2004_27_51.png)

## C'est quoi Flex ?
*Flex* est Un analyseur lexical qui effectue l’analyse lexicale. Il prend en entrée une séquence de caractères individuels et les regroupe en lexèmes. Lex a été crée en 1975 par A. E. Lesk, des laboratoires Bell. La version de GNU est Flex. Il existe une version de Flex pour Ada (Aflex), et une pour Eiffel (Flex/Eiffel). Quant à C++, une version de Lex est disponible avec YACC++.

Flex ajoute des fonctionnalités à Lex (analyse sur plusieurs fichiers, analyse à partir de chaînes en mémoire ... qui ne seront pas exposées ici. Une version acceptant des caractères sur 16 bits existe aussi, Zflex.

## C'est quoi Bison ?
*Bison* est L’analyseur syntaxique qui prend en entrée une suite d’unités lexicales et vérifie qu’elle respecte la grammaire du langage source. Crée en 1974 par S. C. Johnson. La version de GNU est Bison. Il existe des versions pour Ada (Ayacc), une pour Eiffel (Bison/Eiffel). La version C++, avec certaines extensions, est YACC++. Zyacc et BTyacc offrent quant à eux des extensions intéressantes.

Yacc & Bison sont invoqués par l'une des deux commandes :
```shell
yacc option fichier
bison option fichier
```
L’option ***–v*** produit les tables d’analyse sur le fichier nom.output

L’option ***–d*** produit un fichier *nom.tab.h* ( *y.tab.h* avec Yacc) qui contient les définitions des lexémes et le type des attributs, pour permettre l’interface avec l’analyseur lexical entre autre.

L’analyseur lexical n’est pas obligatoirement Flex. Il est fréquent qu’il soit
programmé à la main, et inclus dans le fichier **Bison** ou **Yacc** (Selon l’utilisation).
