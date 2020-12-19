%{
#include "par.tab.h"
%}

%%

[ab10]               {  yylval.car = yytext[0];
                        return Terminal;	}
a/[ab10"("]          {  unput('^');	unput('a');	}
b/[ab10"("]          {  unput('^');	unput('b');	}
1/[ab10"("]          {  unput('^');	unput('1');	}
0/[ab10"("]          {  unput('^');	unput('0');	}
")"/[ab10"("]        {  unput('^');	unput(')');	}
"*"/[ab10"("]        {  unput('^');	unput('*');	}

[ \t]                 ;

"<"[ab1]+">"     {  yylval.chaine = yytext; return Word;	  }

[Gg]etout        {  yylval.chaine = yytext;	return Getout;	  }
[Hh]elp          {  yylval.chaine = yytext;	return Help;      }

[Ii]s            {  yylval.chaine = yytext;	return Is;        }
[Ii]n            {  yylval.chaine = yytext;	return In;        }
[Nn]ullable      {  yylval.chaine = yytext;	return Nullable;  }
[Ee]mpty         {  yylval.chaine = yytext;	return Empty;     }
[Ee]psilon       {  yylval.chaine = yytext;	return Epsilon;   }
[Ss]ingle        {  yylval.chaine = yytext;	return Single;    }
[Ff]inite        {  yylval.chaine = yytext;	return Finite;    }
[Ii]nfinite      {  yylval.chaine = yytext;	return Infinite;  }
[Ss]how" "*      {  yylval.chaine = yytext;	return Show;      }
[Ss]ymbol        {  yylval.chaine = yytext;	return Symbol;    }
[Mm]inimal       {  yylval.chaine = yytext;	return Minimal;   }
[Ll]ength        {  yylval.chaine = yytext;	return Length;    }
[Oo]f            {  yylval.chaine = yytext;	return Of;        }
"?"              {  yylval.chaine = yytext;	return Q;         }
"*"              |
"^"              |		
"|"              |
"("              |
")"              |
"\n"                return *yytext;
.                {  printf("Erreur Lexical : %c n'appartient ni a l'alphabet 'A' ni au simboles conues \n", yytext[0]);	
                    yyterminate();  }
%%







