%{
#include <stdio.h>
#include <string.h>
#include <math.h>
void yyerror(const char *message);
int stack[1000];
int stack_ptr;
%}
%union{
int value;
}
%token <value> INT
%token LOAD
%token ADD
%token SUB
%token MUL
%token MOD
%token INC
%token DEC
%type <value> exp stmt stmts program
%%
program : stmts				{if(stack_ptr == 0){printf("%d\n", stack[0]);}else{printf("Invalid format\n");return(0);}}
		;
stmts : stmt stmts			{}
		| stmt				{}
		;
stmt : exp					{}
		;
exp : LOAD INT				{stack_ptr++; stack[stack_ptr] = $2;}
		| ADD				{
							 if(stack_ptr < 1){printf("Invalid format\n");return(0);}
							 stack[stack_ptr-1] = stack[stack_ptr] + stack[stack_ptr-1];
							 stack_ptr--;
							}
		| SUB				{
							 if(stack_ptr < 1){printf("Invalid format\n");return(0);}
							 stack[stack_ptr-1] = stack[stack_ptr] - stack[stack_ptr-1];
							 stack_ptr--;
							}
		| MUL				{
							 if(stack_ptr < 1){printf("Invalid format\n");return(0);}
							 stack[stack_ptr-1] = stack[stack_ptr] * stack[stack_ptr-1];
							 stack_ptr--;
							}
		| MOD				{
							 if(stack_ptr < 1){printf("Invalid format\n");return(0);}
							 stack[stack_ptr-1] = stack[stack_ptr] % stack[stack_ptr-1];
							 stack_ptr--;
							}
		| INC				{
							 if(stack_ptr < 0){printf("Invalid format\n");return(0);}
							 stack[stack_ptr] = stack[stack_ptr] + 1;
							 
							}
		| DEC				{
							 if(stack_ptr < 0){printf("Invalid format\n");return(0);}
							 stack[stack_ptr] = stack[stack_ptr] - 1;
							 
							}
%%

void yyerror(const char* message){
	printf("%s\n", message);
}

int main(int argc, char* argv[]){
	stack_ptr = -1;
	yyparse();
	return(0);
}