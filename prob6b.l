%{
#include<string.h>
#include<stdlib.h>
#include "atom.h"
#include "prob6b.tab.h"
int col = 0;
%}
%%
\n		{return(0);}
[\t\x20]+	{col += strlen(yytext);}
[0-9]+		{yylval.val = atoi(yytext); col += strlen(yytext); return(INT);}
[A-Z][a-z]*	{strcpy(yylval.el, yytext); col += strlen(yytext); return(ATOM);}
"->"		{yylval.el[0] = yytext[0]; yylval.el[1] = yytext[1]; col += 2; return(CHANGE);}
"+"			{yylval.op = yytext[0]; col += 1; return(ADD);}
"("			{col += 1; return(yytext[0]);}
")"			{col += 1; return(yytext[0]);}
.			{col += 1; return(yytext[0]);}
%%