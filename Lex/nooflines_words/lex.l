%{
#include <stdio.h>

int lines = 0;
int words = 0;
int chars = 0;
%}

%%

[a-zA-Z0-9]+     { words++; chars += yyleng; }  // Match words (letters and numbers)
[ \t]+           { chars += yyleng; }           // Match whitespace, add to character count
\n               { lines++; chars++; }           // Match newline, increment line and character count
.                { chars++; }                    // Match any other character, increment character count

%%

int main(int argc, char *argv[])
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("File opening failed");
            return 1;
        }
    }
    yylex();  // Run the lexical analysis
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    return 0;
}

