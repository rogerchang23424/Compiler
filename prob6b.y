%{
#include <stdio.h>
#include <string.h>
#include "atom.h"
void yyerror(const char *message);
char msg[500];
int has_error = 0;
struct s1 element_append(struct s1 *$1, struct s1 *$2);
void print_atom(struct s1 *$$);
struct s1 deal_result(struct s1* $1, struct s1* $2);
struct s1 result;

int cmpfunc(const void * a, const void * b){
	char * s1 = ((struct s2 *)a)->name;
	char * s2 = ((struct s2 *)b)->name;
	return strcmp(s1, s2);
}
%}
%union{
struct s1 atoms;
int val;
char el[10];
char op;
}
%token <val> INT
%token <el> CHANGE
%token <el> ATOM
%token <op> ADD
%type <atoms> line
%type <atoms> stmt
%type <atoms> formula
%type <atoms> w_element
%type <atoms> element
%type <atoms> atomgroup
%type <atoms> factor
%%
line : stmt	{fprintf(stderr, "line\n");
			 result.len = $1.len;
			 int i;
			 for(i=0;i<$1.len;i++){
				 strcpy(result.atom[i].name, $1.atom[i].name);
				 result.atom[i].total = $1.atom[i].total;
			 }}
	;
stmt: formula CHANGE formula	{fprintf(stderr, "stmt.\n");
								 qsort($1.atom, $1.len, sizeof(struct s2), cmpfunc);
								 print_atom(&$1);
								 qsort($3.atom, $3.len, sizeof(struct s2), cmpfunc);
								 print_atom(&$3);
								 $$ = deal_result(&$1, &$3);
								}
formula: formula ADD w_element	{$$ = element_append(&$1, &$3); fprintf(stderr, "formula add occur.\n"); print_atom(&$$);}
	| w_element					{$$.len = $1.len;
								 int i;
								 for(i=0;i<$1.len;i++){
									 strcpy($$.atom[i].name, $1.atom[i].name);
									 $$.atom[i].total = $1.atom[i].total;
								 }
								fprintf(stderr, "formula status;"); print_atom(&$$);}
	;
w_element: INT element			{$$.len = $2.len;
								 int i;
								 for(i=0;i<$2.len;i++){
									 strcpy($$.atom[i].name, $2.atom[i].name);
									 $$.atom[i].total = $2.atom[i].total * $1;
								 }
								fprintf(stderr, "w_element status;"); print_atom(&$$);}
	| element					{$$.len = $1.len;
								 int i;
								 for(i=0;i<$1.len;i++){
									 strcpy($$.atom[i].name, $1.atom[i].name);
									 $$.atom[i].total = $1.atom[i].total;
								 }
								 fprintf(stderr, "w_element status;"); print_atom(&$$);}
	;
element: element atomgroup		{$$ = element_append(&$1, &$2);fprintf(stderr, "element status;"); print_atom(&$$);}
	| atomgroup					{$$.len = $1.len;
								 int i;
								 for(i=0;i<$1.len;i++){
									 strcpy($$.atom[i].name, $1.atom[i].name);
									 $$.atom[i].total = $1.atom[i].total;
								 }
								fprintf(stderr, "element status;"); print_atom(&$$);}
	;
	
atomgroup: factor INT			{$$.len = $1.len;
								 int i;
								 for(i=0;i<$1.len;i++){
									 strcpy($$.atom[i].name, $1.atom[i].name);
									 $$.atom[i].total = $1.atom[i].total * $2;
								 }
								fprintf(stderr, "atomgroup status;"); print_atom(&$$);}
	| factor					{$$.len = $1.len;
								 int i;
								 for(i=0;i<$1.len;i++){
									 strcpy($$.atom[i].name, $1.atom[i].name);
									 $$.atom[i].total = $1.atom[i].total;
								 }
								 fprintf(stderr, "atomgroup status;"); print_atom(&$$);}
	;
factor: '(' element ')'			{$$.len = $2.len;
								 int i;
								 for(i=0;i<$2.len;i++){
									 strcpy($$.atom[i].name, $2.atom[i].name);
									 $$.atom[i].total = $2.atom[i].total;
								 }
								 fprintf(stderr, "factor status;"); print_atom(&$$);}
	| ATOM						{$$.len = 1; strcpy($$.atom[0].name, $1); $$.atom[0].total = 1;fprintf(stderr, "factor status;"); print_atom(&$$);}
	;
%%

struct s1 element_append(struct s1 *$1, struct s1 *$2){
	int i, j;
	int found = 0;
	struct s1 $$;
	$$.len = $1->len;
	for(i=0;i<$1->len;i++){
		strcpy($$.atom[i].name, $1->atom[i].name);
		$$.atom[i].total = $1->atom[i].total;
	}
	for(i=0;i<$2->len;i++){
		found = 0;
		for(j=0;j<$$.len;j++){
			if(!strcmp($$.atom[j].name, $2->atom[i].name)){
				$$.atom[j].total += $2->atom[i].total;
				found = 1;
				break;
			}
		}
		if(!found){
			strcpy($$.atom[$$.len].name, $2->atom[i].name);
			$$.atom[$$.len].total = $2->atom[i].total;
			$$.len++;
		}
	}
	return $$;
}

struct s1 deal_result(struct s1* $1, struct s1* $2){
	int cmp;
	int i, j;
	i = j = 0;
	struct s1 $$;
	$$.len = 0;
	while(i < $1->len && j < $2->len){
		cmp = strcmp($1->atom[i].name, $2->atom[j].name);
		if(cmp < 0){
			strcpy($$.atom[$$.len].name, $1->atom[i].name);
			$$.atom[$$.len].total = $1->atom[i].total;
			i++;
			$$.len++;
		}else if(cmp == 0){
			strcpy($$.atom[$$.len].name, $1->atom[i].name);
			$$.atom[$$.len].total = $1->atom[i].total - $2->atom[j].total;
			i++; j++;
			$$.len++;
		}else{
			strcpy($$.atom[$$.len].name, $2->atom[j].name);
			$$.atom[$$.len].total = -$2->atom[j].total;
			j++;
			$$.len++;
		}
	}
	while(i < $1->len){
		strcpy($$.atom[$$.len].name, $1->atom[i].name);
		$$.atom[$$.len].total = $1->atom[i].total;
		i++;
		$$.len++;
	}
	while(j < $2->len){
		strcpy($$.atom[$$.len].name, $2->atom[j].name);
		$$.atom[$$.len].total = -$2->atom[j].total;
		j++;
		$$.len++;
	}
	return $$;
}

void print_atom(struct s1 *$$){
	int i;
	fprintf(stderr, "Atom length: %d; ", $$->len);
	for(i=0;i<$$->len;i++){
		fprintf(stderr, "Atom name: %s; Atom total: %d ;", $$->atom[i].name, $$->atom[i].total);
	}
	fprintf(stderr, "\n");
}

void yyerror(const char* message){
	printf("%s\n", "Invalid format");
	has_error=2;
}

int main(int argc, char* argv[]){
	yyparse();
	
	int i;
	for(i=0;i<result.len;i++){
		if(result.atom[i].total)
			printf("%s %d\n", result.atom[i].name, result.atom[i].total);
	}
	
	return(0);
}