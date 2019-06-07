%{
#include <stdio.h>
#include <string.h>
void yyerror(const char *message);
char msg[500];
%}
%union{
struct s2{
	int col;
	int row;
}mat;
int value;
int col;
}
%token <value> INT
%token <col> LPA
%token <col> LMA
%token <col> UT
%token <col> ADDER
%token <col> SUB
%token <col> MUL
%type <mat> expr
%type <mat> term1
%type <mat> term2
%type <mat> factor
%type <mat> matrix
%%
line :expr	{printf("Accepted\n");}
	;
expr :expr ADDER term1	{if($1.col == $3.col && $1.row == $3.row){
							$$ = $1;}
						else{printf("Semantic error on col %d\n", $2);return(0);}}
						
	| expr SUB term1	{if($1.col == $3.col && $1.row == $3.row){
							$$ = $1;}
						else{printf("Semantic error on col %d\n", $2);return(0);}}
						
	| term1	{$$ = $1;}
	;
term1: term1 MUL term2	{if($1.col == $3.row){
							$$.row = $1.row; $$.col = $3.col;}
						else{printf("Semantic error on col %d\n", $2);return(0);}}
						
	| term2	{$$ = $1;}
	;
term2: term2 UT	{$$.col = $1.row; $$.row = $1.col;}
	| factor	{$$ = $1;}
	;
factor : LPA expr ')'	{$$ = $2;}
	| matrix
	;
matrix : LMA INT ',' INT ']'	{$$.row = $2; $$.col = $4;}
	;
%%

void yyerror(const char* message){
	printf("%s\n", "Syntax error");
}

int main(int argc, char* argv[]){
	yyparse();
	return(0);
}