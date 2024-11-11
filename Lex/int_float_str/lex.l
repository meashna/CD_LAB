%{
#include <stdio.h>
%}

%%

[0-9]+\.[0-9]*      { printf("Found a floating point number: %s\n", yytext); }
\.[0-9]+            { printf("Found a floating point number: %s\n", yytext); }
[0-9]+              { printf("Found an integer: %s\n", yytext); }
\.                  { printf("Found a point: %s\n", yytext); }
[a-zA-Z]+           { printf("Found a string: %s\n", yytext); }
[ \t\n]+            { /* Ignore whitespace */ }
.                   { printf("Unknown character: %s\n", yytext); }

%%

int main()
{
    yylex();
    return 0;
}

