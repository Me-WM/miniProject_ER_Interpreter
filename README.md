# Interpréteur pour les expressions régulières sur l’alphabet A = {a, b}
L’objectif de ce mini projet est la réalisation (en Flex et Bison) d’un interpréteur pour les expressions régulières sur l’alphabet A = {a, b}. Cet interpréteur assure un ensemble d’opérations, on note une petite partie :
• vérifier si une expression tapée est une expression régulière valide ;
• calculer la taille d’une telle expression ;
• afficher l’AST d’une expression régulière ;
• ... ;

Le Code source est un peu volumineux, pour cela il est distribué sur quatre fichiers
sources :
-> par.y : qui va contenir le code Bison de l’analyseur syntaxique ;
-> sca.lex : qui va contenir le code Flex de l’analyseur lexical ;
-> ast.h : qui va contenir les structures de données et les routines nécessaires pour la création et la manipulation des arbres abstraits ;
-> ast.c : qui va contenir la définition de ces routines (le code C) ;

#1) Flex :
Flex est Un analyseur lexical qui effectue l’analyse lexicale. Il prend en entrée une
séquence de caractères individuels et les regroupe en lexèmes. Lex a été crée en1975 par
A. E. Lesk, des laboratoires Bell. La version de GNU est Flex. Il existe une version de Flex
pour Ada (Aflex), et une pour Eiffel (Flex/Eiffel). Quant à C++, une version de Lex est
disponible avec YACC++.
Flex ajoute des fonctionnalités à Lex (analyse sur plusieurs fichiers, analyse à partir
de chaînes en mémoire ... qui ne seront pas exposées ici. Une version acceptant des
caractères sur 16 bits existe aussi, Zflex.

#2) Bison
Bison est L’analyseur syntaxique qui prend en entrée une suite d’unités lexicales et
vérifie qu’elle respecte la grammaire du langage source. Crée en 1974 par S. C. Johnson.
La version de GNU est Bison. Il existe des versions pour Ada (Ayacc), une pour Eiffel
(Bison/Eiffel). La version C++, avec certaines extensions, est YACC++. Zyacc et BTyacc
offrent quant à eux des extensions intéressantes.
Yacc & Bison sont invoqués par les commandes :
. Ou
L’option –v produit les tables d’analyse sur le fichier nom.output L’option –d produit
un fichier nom.tab.h ( y.tab.h avec Yacc) qui contient les définitions des lexémes et le type
des attributs, pour permettre l’interface avec l’analyseur lexical entre autre.
L’analyseur lexical n’est pas obligatoirement Flex. Il est fréquent qu’il soit
programmé à la main, et inclus dans le fichier Bison ou Yacc (Selon l’utilisation).
