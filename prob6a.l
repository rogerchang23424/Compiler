%{
#include<string.h>
#include<stdlib.h>
#include "prob6a.tab.h"
int col = 1;
%}
%%
\n		{return(0);}
[\t\x20]+	{col += strlen(yytext);}
[0-9]+		{yylval.value = atoi(yytext); col += strlen(yytext); return(INT);}
"("			{yylval.col = col; col += 1; return(LPA);}
"["			{yylval.col = col; col += 1; return(LMA);}
"^T"		{yylval.col = col; col += 2; return(UT);}
"+"			{yylval.col = col; col += 1; return(ADDER);}
"-"			{yylval.col = col; col += 1; return(SUB);}
"*"			{yylval.col = col; col += 1; return(MUL);}
")"|"^"|"T"|","|"]"	{col += 1; return(yytext[0]);}
.			{col += 1; return(yytext[0]);}
%%