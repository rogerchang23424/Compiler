%{
unsigned int is_blank=0;
#include <string.h>
%}
word	[A-Z][a-zA-Z]*
byte	([01]?[0-9]{1,2}|25[0-5]|2[0-4][0-9])
ipv4	{byte}\.{byte}\.{byte}\.{byte}
email	[a-zA-Z0-9]+\@[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)+
%%
^{word}$	printf("%s is a word\n", yytext);
^{ipv4}$	printf("%s is an IP address\n", yytext);
^{email}$	printf("%s is an email address\n", yytext);
.		;
\n		{printf("");}
%%
int main(int argc, char** argv){
		yylex();
		return(0);
}