#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* tab[100];
static int M=0;
struct ast
{
	enum { CONCAT, UNION, ETOILE, A, B, EPSILON, VIDE } type;
	struct ast *fg; /* fils gauche */
	struct ast *fd; /* fils droit */
};


struct ast* creer_a();                                    /* creation de l'AST (a) */
struct ast* creer_b();                                    /* creation de l'AST (b) */
struct ast* creer_epsilon();                              /* creation de l'AST (e) */
struct ast* creer_vide();                                 /* creation de l'AST (Ø) */
struct ast* creer_union(struct ast *, struct ast *);	  /* creation de l'AST Concatenation */
struct ast* creer_concat(struct ast *, struct ast *);	  /* creation de l'AST Union */
struct ast* creer_etoile(struct ast *);                   /* creation de l'AST étoile */
struct ast* copier_ast(struct ast *);                     /* creation d'une copie d'AST */

void remplir_elements_ast(struct ast *);                  /* Remplir les elements du tableau tab[] */
void imprimer_ast(struct ast *);                          /* Imprime les elements dans le fichier ast.xml */
void liberer_ast(struct ast *);                           /* efface l'AST donner en argument & libere la memoire  */
int est_x(struct ast* , int );                            /* test si l'AST est un element (a) ou (b) */
void aide(void);                                          /* Affiche l'aide sur l'interpreteur */
void start(void);                                         /* Affiche un petit guide au debut */

struct ast* residuel(char , struct ast *);                /* calcule l'AST du résiduel de e */
int appartient(char* , struct ast *);                     /* teste si un mot w appartient à  L(e) */
int contient_epsilon(struct ast *);                       /* teste si epsilon appartient à  L(e) */
int est_epsilon(struct ast*);                             /* teste si L(e) = {epsilon} */
int est_symbole(struct ast*);                             /* teste si L(e) = {a} ou L(e) = {b} */
int est_single(struct ast*);                              /* teste si L(e) contient un seul mot */
int est_vide(struct ast*);                                /* teste si L(e) est vide */
int est_fini(struct ast*);                                /* teste si L(e) est fini */
int calc_minimal(struct ast*);                            /* Donne la Longueur minimal d'une expretion reguliere */


/********************************************************************************************/
/****************************Pour La Compilation On Utilise**********************************/
/****************************************      **********************************************/
/***********                          bison -d par.y                      *******************/
/***********                          flex sca.flex                       *******************/
/***********          gcc -o try par.tab.c lex.yy.c ast.c -ly -lfl        *******************/
/***********                          ./try | try                         *******************/
/********************************************************************************************/


