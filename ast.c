#include "ast.h"

void main(void)
{	start();
	yyparse();
}
                                                                          /********************************************/
                                                                         /****** Affiche un petit gide au debut ******/
void start(void)                                                        /********************************************/
{	printf("\n\t####################################################\
            \n\t################### Mini-Projet ####################\
            \n\t####################################################\
            \n\t# Interpreteur pour les expressions regulieres sur #\
            \n\t#            Alphabet de base = {a, b}             #\
            \n\t#                    UMP - FSO                     #\
            \n\t#                  Janvier--2015                   #\
            \n\t#               Made by : W. KHIATI                #\
            \n\t####################################################\n\
            \n\t>>  Taper la commande Help pour lire l'Aide        \
            \n\t>>  Taper une expression reguliere                 \
            \n\t>>  Taper une Question Is...                       \
            \n\t>>  Taper 'Show ER' pour avoir l'affichage de l'AST\
            \n\t    de l'expression reguliere 'ER'                 \
            \n\t>>  Taper la commande 'Getout' pour quitter l'application\
            \n\n\t>\t");
}
                                                                                      /********************************/
struct ast* creer_a()                                                                /****** création l'AST (a) ******/
{	struct ast *a;                                                                  /********************************/
	a = (struct ast*) malloc(sizeof(struct ast));         
	(*a).type = A;    (*a).fg = NULL;    (*a).fd = NULL;
	return a;
}                                                                                     /********************************/
struct ast* creer_b()                                                                /****** création l'AST (b) ******/	
{	struct ast *b;                                                                  /********************************/
	b = (struct ast*) malloc(sizeof(struct ast));
	(*b).type = B;    (*b).fg = NULL;    (*b).fd = NULL;
	return b;
}                                                                                     /********************************/
struct ast* creer_epsilon()                                                          /****** création l'AST (e) ******/
{	struct ast *e;                                                                  /********************************/
	e = (struct ast*) malloc(sizeof(struct ast));
	e->type = EPSILON;    e->fg = NULL;    e->fd = NULL;
	return e;
}                                                                                     /********************************/
struct ast* creer_vide()                                                             /****** création l'AST (Ø) ******/	
{	struct ast *v;                                                                  /********************************/
	v = (struct ast*) malloc(sizeof(struct ast));
	v->type = VIDE;    v->fg = NULL;    v->fd = NULL;
	return v;
}                                                                                     /********************************/
struct ast* creer_union(struct ast *e1,struct ast *e2)                               /******* création d'Union *******/	
{	struct ast *u;                                                                  /********************************/
	u = (struct ast*) malloc(sizeof(struct ast));
	u->type = UNION;	u->fg = e1;	u->fd = e2;
	return u;
}                                                                                     /********************************/
struct ast* creer_concat(struct ast *e1,struct ast *e2)                              /* création de la Concaténation */
{	struct ast *c;                                                                  /********************************/
	c = (struct ast*) malloc(sizeof(struct ast));
	c->type = CONCAT;    c->fg = e1;    c->fd = e2;
	return c;
}                                                                                     /********************************/
struct ast* creer_etoile(struct ast *e)                                              /***** création de l'étoile *****/	
{	struct ast *s;                                                                  /********************************/
	s = (struct ast*) malloc(sizeof(struct ast));
	(*s).type = ETOILE;    (*s).fg = e;    (*s).fd = NULL;
	return s;
}                                                                                     /********************************/
struct ast* copier_ast(struct ast *e)                                                /***** duplication de l'AST *****/	
{	struct ast *cp;                                                                 /********************************/
	cp = (struct ast*) malloc(sizeof(struct ast));
	cp->type = e->type;
	if (e->fg) cp->fg = copier_ast(e->fg);
	else 	     cp->fg = NULL;
	if (e->fd) cp->fd = copier_ast(e->fd);
	else 	     cp->fd = NULL;
	return cp;
}
                                                              /*******************************************************/
void remplir_elements_ast(struct ast *e)                     /* Remplir les élements de l'AST dant le tableau tab[] */	
{	int j;                                                  /*******************************************************/
      switch(e->type)
      { case A       : tab[M] = (char*) malloc(sizeof(char) * 5);  for(j=0;j<5;j++)  tab[M][j]="<a/>"[j];       M++;  break;
        case B       : tab[M] = (char*) malloc(sizeof(char) * 5);  for(j=0;j<5;j++)  tab[M][j]="<b/>"[j];       M++;  break;
        case EPSILON : tab[M] = (char*) malloc(sizeof(char) * 11); for(j=0;j<11;j++) tab[M][j]="<epsilon/>"[j]; M++;  break;
        case VIDE    : tab[M] = (char*) malloc(sizeof(char) * 8);  for(j=0;j<8;j++)  tab[M][j]="<vide/>"[j];    M++;  break;
        case CONCAT  : tab[M] = (char*) malloc(sizeof(char) * 9);  for(j=0;j<9;j++)  tab[M][j]="<concat>"[j];   M++;  
                       remplir_elements_ast(e->fg);
                       remplir_elements_ast(e->fd);
                       tab[M] = (char*) malloc(sizeof(char) * 10); for(j=0;j<10;j++) tab[M][j]="</concat>"[j];  M++;  break;
        case UNION   : tab[M] = (char*) malloc(sizeof(char) * 8);  for(j=0;j<8;j++)  tab[M][j]="<union>"[j];    M++;  
                       remplir_elements_ast(e->fg);
                       remplir_elements_ast(e->fd);
                       tab[M] = (char*) malloc(sizeof(char) * 9);  for(j=0;j<9;j++) tab[M][j]="</union>"[j];     M++; break;
        case ETOILE  : tab[M] = (char*) malloc(sizeof(char) * 9);  for(j=0;j<9;j++) tab[M][j]="<etoile>"[j];     M++;  
                       remplir_elements_ast(e->fg); 
                       tab[M] = (char*) malloc(sizeof(char) * 10); for(j=0;j<10;j++) tab[M][j]="</etoile>"[j];   M++; break;
      }
}
                                                      /***************************************************************/
void imprimer_ast(struct ast *e)                     /* Imprime les élements dans le fichier ast.xml & les afficher */
{	FILE* fp;                                       /***************************************************************/
	int i;
	remplir_elements_ast(e);
	fp = fopen("ast.xml", "w");
	fputs("<ast>\n", fp) ;                          /* Imprétion sur le fichier ast.xml */
	for(i=0;i<M;i++) fputs(tab[i], fp) ;
	fputs("</ast>", fp) ;
	fclose(fp);
	puts("<ast>");                                  /* Imprétion sur la sortie standart (l'écran) */
	for(i=0;i<M;i++) puts(tab[i]) ;
	puts("</ast>");
	for(i=0;i<M;i++) free(tab[i]);
	M=0;
}
                                                                           /******************************************/
int contient_epsilon(struct ast *e)                                       /*** teste si epsilon appartient à L(e) ***/
{	switch(e->type)                                                      /******************************************/     
	{	case EPSILON : return 1;
		case CONCAT	 : return contient_epsilon(e->fg) && contient_epsilon(e->fd);
		case UNION   : return contient_epsilon(e->fg) || contient_epsilon(e->fd);
		case ETOILE  : return 1;
		default	     : return 0;
	}
}
                                                                                /*************************************/
int est_symbole(struct ast *e)                                                 /* teste si L(e) = {a} ou L(e) = {b} */
{	return (est_x(e,3) && !est_x(e,4)) || (est_x(e,4) && !est_x(e,3)) ;  }    /*************************************/
                               
int est_x(struct ast *x, int T)                                       /*********************************************/       
{	if(x->type==A && T==3) return 1;                                 /** test si l'AST est un élement (a) ou (b) **/
	if(x->type==B && T==4) return 1;                                /*********************************************/
	switch(x->type)
	{	case UNION  :  if(( est_x(x->fg,T) && est_vide(x->fd) )||( est_x(x->fd,T) && est_vide(x->fg) ))
                                                             return 1;
                       return 0;
		case CONCAT :  return ( est_x(x->fg,T) && est_epsilon(x->fd) )||( est_x(x->fd,T) && est_epsilon(x->fg) );
		default     :  return 0;
	}
}
                                                                                   /**********************************/
struct ast* residuel(char s, struct ast *e)                                       /* calcule l'AST du résiduel de e */
{	switch(e->type)                                                              /**********************************/
	{	case A       : if(s=='a')   return creer_epsilon();    return creer_vide();
		case B       : if(s=='b')   return creer_epsilon();    return creer_vide();
		case EPSILON : if(s=='1')   return creer_epsilon();    return creer_vide();
		case VIDE    : return creer_vide();
		
        case CONCAT  : if(est_epsilon(e->fg))			       return residuel(s,e->fd);
                       if(est_epsilon(e->fd))			       return residuel(s,e->fg);
                       if(est_vide(e->fg) || est_vide(e->fd))  return creer_vide();
                       if(!contient_epsilon(e->fg))		       return creer_concat(residuel(s,(*e).fg) , (*e).fd);
                       return creer_union(creer_concat(residuel(s,(*e).fg),(*e).fd)  , residuel(s,(*e).fd) );

		case UNION   : if(est_vide(e->fg))				       return residuel(s,e->fd);
                       if(est_vide(e->fd))				       return residuel(s,e->fg);
                       return creer_union(residuel(s,(*e).fg) , residuel(s,(*e).fd) );
								
		case ETOILE  : if(s=='1')                              return e;
                       return creer_concat(residuel(s,(*e).fg) , creer_etoile(e->fg)) ;
	}
}
                                                                            /*****************************************/
int appartient(char *w, struct ast *e)                                     /** teste si un mot w appartient à  L(e) **/
{	int i=1;                                                              /*****************************************/
	while(w[i]!='>')
	{	e=residuel(w[i],e);
		if(e->type==VIDE)	return 0;
		i++;
	}
	if(contient_epsilon(e)) 	return 1;
	return 0;
}
                                                                               /**************************************/
int est_vide(struct ast* e)                                                   /******* teste si L(e) est vide *******/
{	switch(e->type)                                                          /**************************************/
	{	case VIDE   :  return 1;
		case CONCAT :  return est_vide(e->fg) || est_vide(e->fd);
		case UNION  :  return est_vide(e->fg) && est_vide(e->fd);
		default 	:  return 0;
	}
}
                                                                                /*************************************/
int est_epsilon(struct ast* e)                                                 /***** teste si L(e) = {epsilon} *****/
{	switch(e->type)                                                           /*************************************/
	{	case EPSILON : return 1;
		case UNION   : if(est_vide(e->fg) || est_vide(e->fd))	
                                return est_epsilon(e->fd) || est_epsilon(e->fg);
		case CONCAT  : return est_epsilon(e->fg) && est_epsilon(e->fd);
        case ETOILE  : if(est_vide(e->fg) || est_epsilon(e->fg))       return 1;
		default :	   return 0;
	}
}
                                                                               /**************************************/
int est_single(struct ast* e)                                                 /* teste si L(e) contient un seul mot */
{	switch(e->type)                                                          /**************************************/
	{	case CONCAT	:  return est_single(e->fg) && est_single(e->fd);
		case UNION  :  return (est_vide(e->fd) && est_single(e->fg)) || (est_vide(e->fg) && est_single(e->fd));
		case ETOILE :  return est_epsilon(e->fg) || est_vide(e->fg);
		case VIDE   :  return 0;
		default	    :  return 1;
	}	
}
                                                                                 /************************************/
int est_fini(struct ast* e)                                                     /****** teste si L(e) est fini ******/
{	switch(e->type)                                                            /************************************/
	{	case CONCAT	:  
		case UNION  :  return est_fini(e->fg) && est_fini(e->fd);
		case ETOILE :  return est_epsilon(e->fg) || est_vide(e->fg);
		default     :  return 1;
	}
}
                                                             /********************************************************/
void liberer_ast(struct ast *e)                             /* efface l'AST donner en argument & libère la mémoire  */
{	switch(e->type)                                        /********************************************************/
	{	case CONCAT	:  
		case UNION  :  free(e->fd);
		case ETOILE :  free(e->fg);	break;
		default     :  free(e);		break;
	}
}
                                                                          /*******************************************/
void aide(void)                                                          /**** Affiche l'aide sur l'interpreteur ****/
{	                                                                    /*******************************************/
	printf("\t\
 _______________________________________________________________\n\t\
| PROJECT :                                                     |\n\t\
|  Regular Expression Calculator over the alphabet A = {a, b}   |\n\t\
|                                                               |\n\t\
| AUTHOR :                                                      |\n\t\
|  This interpreter was written by Wassim KHIATI                |\n\t\
|  Student in UMP - FSO.                                        |\n\t\
|  Demand by our Professor A.DARGHAM as a Projet Home work      |\n\t\
|                                                               |\n\t\
| COMMANDES :                                                   |\n\t\
|  Help                                                         |\n\t\
|    Affiche l'aide sur l'interpreteur                          |\n\t\
|                                                               |\n\t\
|  Getout                                                       |\n\t\
|    Quitte l'interpreteur                                      |\n\t\
|                                                               |\n\t\
|  exp                                                          |\n\t\
|    Verifier si exp est une expression reguliere valide        |\n\t\
|    Affiche egalement sa taille                                |\n\t\
|                                                               |\n\t\
|  Is exp Nullable ?                                            |\n\t\
|    Teste si L(exp) contient le mot vide (epsilon)             |\n\t\
|                                                               |\n\t\
|  Is <word> In exp ?                                           |\n\t\
|    Teste si L(exp) contient le mot donne (word)               |\n\t\
|                                                               |\n\t\
|  Is exp Empty ?                                               |\n\t\
|    Teste si L(exp) est vide                                   |\n\t\
|                                                               |\n\t\
|  Is exp Finite ?                                              |\n\t\
|    Teste si L(exp) est fini                                   |\n\t\
|                                                               |\n\t\
|  Is exp Infinite ?                                            |\n\t\
|    Teste si L(exp) est infini                                 |\n\t\
|                                                               |\n\t\
|  Is exp Symbole ?                                             |\n\t\
|    Teste si L(exp) est {a} ou bien {b} (un symbole)           |\n\t\
|                                                               |\n\t\
|  Is exp Single ?                                              |\n\t\
|    Teste si L(exp) est un singleton (reduit a un seul mot)    |\n\t\
|                                                               |\n\t\
|  Show exp                                                     |\n\t\
|    Cree un fichier XML nomme ast.xml representant l'AST de exp|\n\t\
|    Affiche egalement le contenu de ce fichier                 |\n\t\
|                                                               |\n\t\
|  Minimal Length Of exp                                        |\n\t\
|    Determine la longeur minimal de l'epretion reguliere 'exp' |\n\t\
|_______________________________________________________________|\n\n");

system("pause"); /* system("echo Qaunt vous finissez la lecture, Clique sur ENTRER"); */
system("cls")   /*  system("read a"); /*
               /* system("clear"); /*
}
                                                             /********************************************************/
int calc_minimal(struct ast *e)                             /* Donne la Longueur minimal de expretion reguliere 'e' */
{   if(est_vide(e))            return -1;                  /********************************************************/
    if(contient_epsilon(e))    return  0;
    switch(e->type)
    {    case CONCAT : return calc_minimal(e->fg) + calc_minimal(e->fd);
         case UNION  : if(calc_minimal(e->fg) > calc_minimal(e->fd))
                                           return calc_minimal(e->fd);
                       return calc_minimal(e->fg);
        default      : return 1;
    }
}







