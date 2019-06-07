%{
unsigned int is_blank=0;
#include <string.h>
void print_hex(char* str){
		int i;
		for(i=0;i<strlen(str);i++){
			if(!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
				printf("%c", str[i]);
			}
		printf("\n");
}
%}
hex			0[xX][0-9a-fA-F]{1,8}
%%
^{hex}$	printf("%s\n", yytext);
(\x20|\x09|\x0a)+{hex}$	print_hex(yytext);
^{hex}(\x20|\x09|\x0a)+	print_hex(yytext);
(\x20|\x09|\x0a){hex}(\x20|\x09|\x0a)	print_hex(yytext);
.		;
\n		{printf("");}
%%
int main(int argc, char** argv){
		yylex();
		return(0);
}