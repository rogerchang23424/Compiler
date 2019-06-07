%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "test.tab.h"
int col = 0;
int len;
%}
%%
"\n"		{;}
[\t\x20]+	{;}
"add"		{return(ADD);}
"sub"		{return(SUB);}
"mul"		{return(MUL);}
"mod"		{return(MOD);}
"inc"		{return(INC);}
"dec"		{return(DEC);}
"load"		{return(LOAD);}
[+-]?[0-9]+		{yylval.value = atoi(yytext); return(INT);}
<<EOF>>		{return(0);}
.		{}
%%