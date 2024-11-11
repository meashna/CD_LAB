%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;
%}

%%

[aAeEiIoOuU]    { vowels++; }          // Match vowels (both uppercase and lowercase)
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonants++; } // Match consonants (both uppercase and lowercase)
.               { /* Ignore any other character */ }

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
    printf("Number of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);
    return 0;
}

