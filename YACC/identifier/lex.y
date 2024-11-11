%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);

int valid = 1;
%}

%token IDENTIFIER DIGIT EOL

%%

start:
    input
    ;

input:
      IDENTIFIER EOL
        { printf("It is a valid identifier.\n"); }
    | DIGIT EOL
        { printf("It is not a valid identifier.\n"); }
    | EOL
        { /* Handle empty input */ }
    | error EOL
        { yyerror("Invalid input"); }
    ;

%%

void yyerror(const char *s) {
    printf("It is not a valid identifier.\n");
}

int main() {
    printf("Enter a name to test for identifier: ");
    yyparse();
    return 0;
}

