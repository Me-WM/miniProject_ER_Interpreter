%{
#include "ast.h"
int Nbr=0;
%}

%start input

%union {  struct ast* astval;
          char* chaine;
          char car;
       }
%type <astval> ER

%token <car> Terminal

%token <chaine> Q
%token <chaine> Is
%token <chaine> In
%token <chaine> Of
%token <chaine> Word
%token <chaine> Help
%token <chaine> Show
%token <chaine> Empty
%token <chaine> Single
%token <chaine> Finite
%token <chaine> Getout
%token <chaine> Symbol
%token <chaine> Length
%token <chaine> Minimal
%token <chaine> Epsilon
%token <chaine> Infinite
%token <chaine> Nullable

%nonassoc '(' ')'
%left '|'
%left '^'
%left '*'

%%

input :  
      |  input line             { printf("\t>\t");
                                  Nbr=0;
                                }
      |  input Getout '\n'      { printf("(^_^) Have a nice day.\n\n");
                                  sleep(2);
                                  exit(0);
                                }
      |  input Help '\n'        { aide();
                                  start();
                                }
;
line  :  '\n'			   
      |  ER '\n'                { printf("\tValide, taille = %d \n",Nbr);
                                  liberer_ast($1);
                                }
      |  Show ER '\n'           { imprimer_ast($2);
                                  liberer_ast($2); 
                                }
      |  Is ER Nullable Q '\n'  { if(contient_epsilon($2))    printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n");
                                  liberer_ast($2); 
                                }
      |  Is ER Empty Q '\n'     { if(est_vide($2))			printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Is ER Epsilon Q '\n'   { if(est_epsilon($2))         printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Is ER Single Q '\n'    { if(est_single($2))          printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Is ER Finite Q '\n'    { if(est_fini($2))            printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Is ER Infinite Q '\n'  { if(!est_fini($2))           printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Is Word In ER Q '\n'   { if(appartient($2,$4))       printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($4);
                                }
      |  Is ER Symbol Q '\n'    { if(est_symbole($2))         printf("\t=> Yes\n");
                                  else                        printf("\t=> No\n"); 
                                  liberer_ast($2);
                                }
      |  Minimal Length Of ER '\n'
                                { printf("\t=> %d\n",calc_minimal($4)); 
                                  liberer_ast($4);
                                }
;
ER	:  Terminal		{	switch($1)
						{	case 'a' : $$ = creer_a();		Nbr++;   break;
							case 'b' : $$ = creer_b();		Nbr++;   break;
							case '1' : $$ = creer_epsilon();         break;
							case '0' : $$ = creer_vide();            break;
						}
			 	
                    }
	|  ER '*'		{	Nbr++;
                        $$ = creer_etoile($1);
                    }
	|  ER '|' ER	{	Nbr++;
                        $$ = creer_union($1,$3);
                    }
	|  ER '^' ER	{	Nbr++;
                        $$ = creer_concat($1,$3);
                    }
	|  '(' ER ')'	{	$$ = copier_ast($2);
                    }
;


%%



