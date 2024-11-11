%{
#include <stdio.h>
#include <ctype.h>

// Keywords
char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", NULL
};

// Function to check if a given string is a keyword
int isKeyword(char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*   {
                            if (isKeyword(yytext))
                                printf("%s is a keyword\n", yytext);
                            else
                                printf("%s is an identifier\n", yytext);
                        }

[0-9]+                    { printf("%s is a number\n", yytext); }
"+"|"-"|"*"|"/"|"="       { printf("%s is an operator\n", yytext); }
","|"."|"["|"]"|"{"|"}"   { printf("%s is a special character\n", yytext); }
\n                        { /* Ignore newlines */ }
[ \t]+                    { /* Ignore whitespace */ }

.                         { printf("%s is an unrecognized character\n", yytext); }

%%

int main(int argc, char **argv) {
    // Check if a file is provided as input
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    // Run the lexical analyzer
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

